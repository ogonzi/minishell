/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:39:15 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 12:29:54 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_parser.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

int	split_cmd_line(t_prompt *prompt, char *line)
/*
 * It checks if the input line contains any unbalanced quotes by calling the
 * check_quotes function with line as an argument. If there are unbalanced
 * quotes,	it prints an error message to STDERR_FILENO and returns CATCH_ALL.

 * If the input line doesn't contain any unbalanced quotes, it calls
 * ft_split_mod function with split_line, line, and "|" as arguments. 
 * If ft_split_mod returns TRUE, it means there was an error in splitting
 * the line, and it returns the SHELL_MISUSE status code.
	
 * If the ft_split_mod function successfully splits the input line into an
 * array of strings separated by "|", it passes the resulting split_line array
 * to the set_cmdline function along with the prompt structure. This function
 * parses the command line and sets the prompt->cmdline structure variable
 * accordingly.
	
 * The function then frees the memory allocated for the split_line array using
 * the ft_memfree function (which presumably frees each element of the array
 * as well as the array itself).
*/
{
	ssize_t	idx;
	char	**split_line;
	t_list	*cmd_line_node;

	if (check_quotes(line) == TRUE)
	{
		rl_on_new_line();
		ft_printf_fd(STDERR_FILENO, "%s\n", ERR_QUOTES);
		return (CATCH_ALL);
	}
	if (ft_split_mod(&split_line, line, "|") == TRUE)
		return (SHELL_MISUSE);
	idx = -1;
	while (split_line[++idx])
	{
		set_node(&split_line[idx], &cmd_line_node);
		ft_lstadd_back(&prompt->cmdline, cmd_line_node);
	}
	ft_memfree(split_line);
	return (0);
}

int	check_quotes(char *line)
{
	ssize_t	idx;
	t_bool	f_single_quote;
	t_bool	f_double_quote;

	idx = 0;
	f_single_quote = FALSE;
	f_double_quote = FALSE;
	while (line[idx])
	{
		if (line[idx] == '\'')
			find_closing_quote(line, &idx, &f_single_quote, '\'');
		if (line[idx] == '\"')
			find_closing_quote(line, &idx, &f_double_quote, '\"');
		if (line[idx] != '\0')
			idx++;
	}
	if (f_single_quote == FALSE && f_double_quote == FALSE)
		return (FALSE);
	return (TRUE);
}

void	set_node(char **split_line, t_list **cmd_line_node)
{
	int				cmd_len;
	t_cmdline		*cmd_line_content;

	cmd_len = ft_strlen(*split_line);
	cmd_line_content = malloc(sizeof(t_cmdline));
	if (!cmd_line_content)
		terminate(ERR_MEM, EXIT_FAILURE);
	cmd_line_content->cmd = malloc(sizeof(char) * (cmd_len + 1));
	if (!cmd_line_content->cmd)
		terminate(ERR_MEM, EXIT_FAILURE);
	ft_strlcpy(cmd_line_content->cmd, *split_line, cmd_len + 1);
	*cmd_line_node = ft_lstnew(cmd_line_content);
	if (!*cmd_line_node)
		terminate(ERR_MEM, EXIT_FAILURE);
}
