/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:38:07 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/04 17:40:44 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

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
	if (word_cpy == NULL)
		terminate(ERR_MEM, 1);
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
	free(word_cpy);
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

int	get_env_var_length(char *word, int *i)
{
	int		start;
	char	*env_var;
	int		length_env_var;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	env_var = ft_substr(word, start, *i - start);
	if (env_var == NULL)
		terminate(ERR_MEM, 1);
	length_env_var = ft_strlen(getenv(env_var));
	free(env_var);
	return (length_env_var);
}

char	*get_env_var(char *word, int *i)
{
	int		start;
	char	*env_var;
	char	*expanded_env_var;

	start = *i;
	while (ft_isalnum(word[*i]) || word[*i] == '_')
		(*i)++;
	env_var = ft_substr(word, start, *i - start);
	if (env_var == NULL)
		terminate(ERR_MEM, 1);
	expanded_env_var = getenv(env_var);
	free(env_var);
	return (expanded_env_var);
}

int	new_word_length(char *word)
{
	int	i;
	int	base_length;
	int	added_length;

	i = 0;
	base_length = 0;
	added_length = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			i++;
			added_length += get_env_var_length(word, &i);
		}
		else
		{
			base_length++;
			i++;
		}
	}
	return (base_length + added_length);
}

void	set_new_word(char **word, char *cpy_word)
{
	int	i;
	int	j;
	int	k;
	char	*expanded_env_var;

	i = 0;
	j = 0;
	while (cpy_word[i] != '\0')
	{
		if (cpy_word[i] == '$')
		{
			//start = i;
			i++;
			expanded_env_var = get_env_var(cpy_word, &i);
			k = 0;
			while (expanded_env_var[k] != '\0')
			{
				(*word)[j] = expanded_env_var[k];
				k++;
				j++;
			}
		}
		else
		{
			(*word)[j] = cpy_word[i];
			i++;
			j++;
		}
	}
	(*word)[j] = '\0';
}

void	expand_env(char **word)
{
	int		old_length;
	int		new_length;
	char	*cpy_word;

	new_length = new_word_length(*word);
	old_length = ft_strlen(*word);
	cpy_word = malloc(sizeof(char) * (old_length + 1));
	if (cpy_word == NULL)
		terminate(ERR_MEM, 1);
	ft_strlcpy(cpy_word, *word, old_length + 1);
	free(*word);
	*word = NULL;
	*word = malloc(sizeof(char) * (new_length + 1));
	set_new_word(word, cpy_word);
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
			if (ft_strchr(word, '$'))
				expand_env(&word);
			l_word_cpy = l_word_cpy->next;
		}
		l_cmd_line_cpy = l_cmd_line_cpy->next;
	}
	return (0);
}
