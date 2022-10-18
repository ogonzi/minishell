/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:11:15 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/18 19:58:51 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdio.h>

/*
void	print_list(t_list *lst)
{
	t_cmd_line_content	*cmd_line_content;
	t_list				*lst_cpy;
	int					i;

	lst_cpy = lst;
	i = 0;
	cmd_line_content = malloc(sizeof(t_cmd_line_content));
	while (lst_cpy)
	{
		cmd_line_content = (t_cmd_line_content *)lst_cpy->content;
		printf("%s\n", cmd_line_content[i].cmd);
		lst_cpy = lst_cpy->next;
		i++;
	}
}
*/

int	count_splits(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i] != NULL)
		i++;
	return (i);
}

void	split_cmd_line(t_list **cmd_line, char *line)
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
		//cmd_line_content[i].cmd = malloc(sizeof(char) * (cmd_len + 1));
		cmd_line_content = malloc(sizeof(t_cmd_line_content));
		cmd_line_content->cmd = malloc(sizeof(char) * (cmd_len + 1));
		printf("Alloc cmd_line_content %p\n", cmd_line_content);
		printf("Alloc cmd_line_content->cmd %p\n", cmd_line_content->cmd);
		ft_strlcpy(cmd_line_content->cmd, split_line[i], cmd_len + 1);
		free(split_line[i]);
		cmd_line_node = ft_lstnew(cmd_line_content);
		printf("Alloc node %p\n", cmd_line_node);
		ft_lstadd_back(cmd_line, cmd_line_node);
		i++;
	}
	free(split_line);
	//print_list(*cmd_line);
}
