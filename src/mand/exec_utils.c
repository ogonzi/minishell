/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:10:22 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/17 20:36:48 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void	set_command_array(t_list *token_list, char ***command_array,
								int len_list)
{
	int	i;

	i = 0;
	while (token_list)
	{
		if (((t_token_content *)token_list->content)->type == 1)
		{
			(*command_array)[i]
				= ft_strdup(((t_token_content *)token_list->content)->word);
			if ((*command_array)[i] == NULL)
				terminate(ERR_MEM, 1);
			i++;
		}
		token_list = token_list->next;
	}
	while (i < len_list + 1)
	{
		(*command_array)[i] = NULL;
		i++;
	}
}

char	**get_command_array(t_list *command)
{
	char	**command_array;
	t_list	*token_list;
	int		len_list;

	token_list = ((t_cmd_line_content *)command->content)->word;
	len_list = ft_lstsize(token_list);
	command_array = malloc(sizeof(char *) * (len_list + 1));
	if (command_array == NULL)
		terminate(ERR_MEM, 1);
	set_command_array(token_list, &command_array, len_list);
	return (command_array);
}

char	**get_envp(t_list *environ)
{
	char	**envp;
	int		len_list;
	int		i;

	len_list = ft_lstsize(environ);
	envp = malloc(sizeof(char *) * (len_list + 1));
	if (envp == NULL)
		terminate(ERR_MEM, 1);
	i = 0;
	while (environ)
	{
		envp[i] = ft_strdup(((t_environ_content *)environ->content)->env_var);
		if (envp[i] == NULL)
			terminate(ERR_MEM, 1);
		i++;
		environ = environ->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	dup_to_out(int fd[2], t_list *command)
{
	t_list			*token;
	t_token_content	*token_content;

	token = ((t_cmd_line_content *)command->content)->word;
	while (token)
	{
		token_content = token->content;
		if (token_content->type == EXIT_FILE)
		{
			close(fd[1]);
			fd[1] = open(token_content->word,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (token_content->type == EXIT_FILE_RET)
		{
			close(fd[1]);
			fd[1] = open(token_content->word,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		if (fd[1] < 0)
			terminate(ERR_OPEN, 1);
		token = token->next;
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		terminate(ERR_DUP, 1);
}
