/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:11:15 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 16:19:53 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>
#include <readline/readline.h>

void	set_node(char **split_line, t_list **cmd_line_node)
{
	int					cmd_len;
	t_cmd_line_data	*cmd_line_data;

	cmd_len = ft_strlen(*split_line);
	cmd_line_data = malloc(sizeof(t_cmd_line_data));
	if (cmd_line_data == NULL)
		terminate(ERR_MEM, 1);
	cmd_line_data->cmd = malloc(sizeof(char) * (cmd_len + 1));
	if (cmd_line_data->cmd == NULL)
		terminate(ERR_MEM, 1);
	ft_strlcpy(cmd_line_data->cmd, *split_line, cmd_len + 1);
	*cmd_line_node = ft_lstnew(cmd_line_data);
	if (*cmd_line_node == NULL)
		terminate(ERR_MEM, 1);
}

int	check_quotes(char *line)
{
	int	i;
	int	single_quote_flag;
	int	double_quote_flag;

	single_quote_flag = 0;
	double_quote_flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
			find_closing_quote(line, &i, &single_quote_flag, '\'');
		if (line[i] == '\"')
			find_closing_quote(line, &i, &double_quote_flag, '\"');
		if (line[i] != '\0')
			i++;
	}
	if (single_quote_flag == 0 && double_quote_flag == 0)
		return (0);
	return (1);
}

int	split_cmd_line(t_list **cmd_line, char *line)
{
	int					i;
	t_list				*cmd_line_node;
	char				**split_line;

	if (check_quotes(line) != 0)
	{
		rl_on_new_line();
		printf("%s\n", ERR_QUOTES);
		return (1);
	}
	if (ft_split_mod(&split_line, line, "|") != 0)
		return (2);
	i = 0;
	while (split_line[i] != NULL)
	{
		set_node(&split_line[i], &cmd_line_node);
		ft_lstadd_back(cmd_line, cmd_line_node);
		i++;
	}
	ft_free_twod_memory(split_line);
	return (0);
}
