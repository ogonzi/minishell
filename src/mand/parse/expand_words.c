/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/11/16 18:39:19 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	print_list(t_list *lst)
{
	t_list				*lst_cpy;

	lst_cpy = lst;
	while (lst_cpy)
	{
		printf("%s (%d)\n", ((t_token_content *)lst_cpy->content)->word,
			((t_token_content *)lst_cpy->content)->type);
		lst_cpy = lst_cpy->next;
	}
	lst_cpy = 0;
}

//TODO: When the getenv returns NULL, collapse env_var, for example,
// a$b$USER should become a$USER.
// Also, remove quotes according to quotes rules, for example,
// "a'a"$b'$USER' should become a'a$USER

void	expand(char *word, int *remove_char)
{
	int		i;
	int		start;
	int		single_quote_flag;
	char	*env_var;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
			find_closing_quote(word, &i, &single_quote_flag, '\'');
		if (word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
		{
			i++;
			start = i;
			while (ft_is_in_set(word[i], " \t\r\"$") == 0 && word[i] != '\0')
				i++;
			env_var = ft_substr(word, start, i - start);
			if (ft_strlen(env_var) > 0 && getenv(env_var) == NULL)
			{
				remove_char[start - 1] = 1;
				while (start < i)
				{
					remove_char[start] = 1;
					start++;
				}
			}
			free(env_var);
		}
		else
			i++;
	}
}

void	remove_quotes(char *word, int *remove_char)
{
	int	i;
	int	single_quote_flag;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
		{
			remove_char[i] = 1;
			find_closing_quote(word, &i, &single_quote_flag, '\'');
			remove_char[i] = 1;
		}
		if (word[i] == '\"')
		{
			remove_char[i] = 1;
			find_closing_quote(word, &i, &single_quote_flag, '\"');
			remove_char[i] = 1;
		}
		i++;
	}
}

void	format_word(char *word, int *remove_char)
{
	int		i;
	int		j;
	int		word_len;
	char	*word_cpy;

	word_cpy = ft_strdup(word);
	word_len = ft_strlen(word);
	i = -1;
	j = 0;
	while (++i < word_len)
	{
		if (remove_char[i] == 0)
		{
			word[j] = word_cpy[i];
			j++;
		}
	}
	while (j < word_len)
	{
		word[j] = '\0';
		j++;
	}
}

void	alloc_remove_char(int **remove_char, char *word)
{
	int	word_len;
	int	i;

	word_len = ft_strlen(word);
	*remove_char = malloc(sizeof(int) * word_len);
	if (*remove_char == NULL)
		terminate(ERR_MEM, 1);
	i = -1;
	while (++i < word_len)
		(*remove_char)[i] = 0;
}

int	expand_words(t_list **l_cmd_line)
{
	t_list	*l_cmd_line_cpy;
	t_list	*l_word_cpy;
	char	*word;
	int		*remove_char;

	l_cmd_line_cpy = *l_cmd_line;
	while (l_cmd_line_cpy)
	{
		l_word_cpy = ((t_cmd_line_content *)l_cmd_line_cpy->content)->word;
		while (l_word_cpy)
		{
			word = ((t_token_content *)l_word_cpy->content)->word;
			alloc_remove_char(&remove_char, word);
			expand(word, remove_char);
			remove_quotes(word, remove_char);
			format_word(word, remove_char);
			free(remove_char);
			l_word_cpy = l_word_cpy->next;
		}
		l_cmd_line_cpy = l_cmd_line_cpy->next; 
	}
	return (0);
}
