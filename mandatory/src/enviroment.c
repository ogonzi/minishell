/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:53:44 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/10 16:40:13 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"
#include "mnshll_builtins.h"

static void	*ft_environ_node(char *env);

void	custom_getpid(t_prompt *prompt)
/*
	This function is used to obtain the process ID (PID) of the current shell
	prompt. It does so by forking a new process and then waiting for it to
	finish.

		1.	The pid_t data type is defined to store the process ID, and pid
		variable is declared and initialized to the return value of fork(),
		which creates a new process by duplicating the calling process.

		2.	If fork() returns a negative value, an error occurred and terminate()
		function is called with ERR_FORK error code and a non-zero exit status.
			If fork() returns zero, the current process is the child process,

		3.	The parent process waits for the child process to finish by calling
		waitpid() with the pid of the child process, a NULL pointer for the
		status parameter, and a flag of 0.

		4. Once the child process has finished, waitpid() returns, and the pid
		of the child process minus 1 is stored in the pid field of the t_prompt
		struct pointed to by the prompt parameter.

	Note that subtracting 1 from the child process ID (pid) is done because the
	child process immediately exits with a status code of 1. By subtracting 1,
	the resulting process ID is unique and can be used to identify the current
	shell prompt.
*/
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		terminate(ERR_FORK, EXIT_FAILURE);
	if (pid == 0)
		exit(1);
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

void	set_environ(t_prompt *prompt, char **ev)
/*
	This function is used to initialize the environment variable list for the
	shell. It takes a t_prompt struct pointer and a char pointer to a string
	of environment variables separated by the '=' character.

	Note that the ft_environ_node() function is a helper function used to
	create a new t_env node. It takes a char pointer to an environment
	variable string, splits it into two separate strings for the variable
	name and value, and returns a new t_env node with those fields populated.
*/
{
	ssize_t	idx;
	t_env	*lst;
	t_env	*aux;
	t_env	*tmp;

	idx = -1;
	while (ev[++idx])
	{
		aux = ft_environ_node(ev[idx]);
		if (!aux)
			return ;
		if (idx == 0)
		{
			prompt->env = aux;
			lst = aux;
			continue ;
		}
		tmp = lst;
		lst = aux;
		tmp->next = lst;
	}
}

static void	*ft_environ_node(char *env)
{
	static t_unt	idx = 0;
	t_env			*node;
	char			**str;

	node = malloc(sizeof(t_env));
	if (!node)
		terminate(ERR_MEM, EXIT_FAILURE);
	str = ft_split(env, '=');
	if (!str)
		terminate(ERR_MEM, EXIT_FAILURE);
	node->env_var = str[0];
	node->env_data = str[1];
	node->idx = ++idx;
	node->next = NULL;
	return (node);
}

void	set_custom_env(t_prompt *prompt, char *prog)
/*
	This function sets some values of the enviroment copy that we initialized
	before to the ones we desire for the program.

	See custom_export() function for more information.
*/
{
	char	*val;
	t_env	*aux;

	val = ft_calloc(MS_MAX_PATH, sizeof(char));
	if (!val)
		terminate(ERR_MEM, EXIT_FAILURE);
	if (getcwd(val, MS_MAX_PATH))
		custom_export(ft_env_iter(prompt->env, "PWD"), val);
	ft_delete(val);
	aux = ft_env_iter(prompt->env, "SHLVL");
	custom_export(ft_env_iter(prompt->env, "SHLVL"), aux->env_data);
	aux = NULL;
	custom_export(ft_env_iter(prompt->env, "PATH"), MS_PATH);
	custom_export(ft_env_iter(prompt->env, "_"),
		ft_strjoin(ft_env_iter(prompt->env, "PWD")->env_data,
			ft_strtrim(prog, ".")));
}
