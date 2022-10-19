/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:33:12 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/19 12:22:10 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	del(void *content)
{
	t_cmd_line_content	*cmd_line_content;
	int					i;

	cmd_line_content = content;
	i = 0;
	while (cmd_line_content != NULL)
	{
		free(cmd_line_content[i].cmd);
		i++;
	}
	free(cmd_line_content);

}

void	ft_free(void *content)
{
	t_cmd_line_content	*cmd_line_content;

	cmd_line_content = content;
	printf("Freeing cmd_line_content->cmd %p\n", cmd_line_content->cmd);
	free(cmd_line_content->cmd);
	cmd_line_content->cmd = NULL;
	printf("Freeing cmd_line_content %p\n", cmd_line_content);
	free(cmd_line_content);
}

void	free_cmd_line(t_list *cmd_line)
{
	t_list	*tmp;

	ft_lstiter(cmd_line, &ft_free);
	while(cmd_line)
	{
		tmp = cmd_line->next;
		printf("Freeing node %p\n", cmd_line);
		free(cmd_line);
		cmd_line = tmp;
	}
	cmd_line = NULL;
}