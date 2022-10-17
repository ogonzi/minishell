/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:11:15 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/17 18:30:41 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

void	print_list(t_list *lst)
{
	t_cmd_line_content	*cmd_line_content;

	cmd_line_content = malloc(sizeof(t_cmd_line_content));
	while (lst)
	{
		cmd_line_content = (t_cmd_line_content *)lst->content;
		printf("%s\n", cmd_line_content->cmd);
		lst = lst->next;
	}
}

void	split_cmd_line(t_list *cmd_line, char *line)
{
	char				**split_line;
	int					i;
	int					cmd_len;
	t_list				*cmd_line_node;
	t_cmd_line_content	*cmd_line_content;

	split_line = ft_split(line, '|');
	if (split_line == NULL)
		terminate(ERR_MEM, 1);
	i = 0;
	while (split_line[i] != NULL)
	{
		cmd_len = ft_strlen(split_line[i]);
		cmd_line_content = malloc(sizeof(t_cmd_line_content));
		cmd_line_content->cmd = malloc(sizeof(char) * (cmd_len + 1));
		ft_strlcpy(cmd_line_content->cmd, split_line[i], cmd_len + 1);
		cmd_line_node = ft_lstnew(cmd_line_content);
		ft_lstadd_back(&cmd_line, cmd_line_node);
		i++;
	}
	print_list(cmd_line);
}
