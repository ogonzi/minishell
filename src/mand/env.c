/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:10:13 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/13 17:08:42 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void	set_environ_node(char *env_var, t_list **environ_node)
{
	t_environ_content	*environ_content;

	environ_content = malloc(sizeof(t_environ_content));
	if (environ_content == NULL)
		terminate(ERR_MEM, 1);
	environ_content->env_var = ft_strdup(env_var);
	if (environ_content->env_var == NULL)
		terminate(ERR_MEM, 1);
	*environ_node = ft_lstnew(environ_content);
	if (*environ_node == NULL)
		terminate(ERR_MEM, 1);
}

void	set_environ(t_prompt *prompt, char *envp[])
{
	int		i;
	t_list	*environ_node;

	i = 0;
	while (envp[i] != NULL)
	{
		set_environ_node(envp[i], &environ_node);
		ft_lstadd_back(&prompt->environ, environ_node);
		i++;
	}
}

void	custom_setenv(char *name, char *value, t_prompt *prompt)
{
	char	*aux[2];
	t_list	*environ_node;

	aux[0] = ft_strjoin(name, "=");
	if (aux[0] == NULL)
		terminate(ERR_MEM, 1);
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	set_environ_node(aux[1], &environ_node);
	ft_lstadd_back(&prompt->environ, environ_node);
	free(aux[1]);
}

char	*custom_getenv(char *name, t_prompt *prompt)
{
	t_list	*environ_copy;
	int		name_length;
	char	*env_var;
	char	*value;

	environ_copy = prompt->environ;
	name_length = ft_strlen(name);
	while (environ_copy)
	{
		env_var = ((t_environ_content *)environ_copy->content)->env_var;
		if (ft_strncmp(env_var, name, name_length) == 0 && env_var[name_length] == '=')
		{
			value = ft_substr(env_var, name_length + 1, ft_strlen(env_var) - name_length + 1);
			if (value == NULL)
				terminate(ERR_MEM, 1);
			return (value);
		}
		environ_copy = environ_copy->next;
	}
	return (0);
}

void	init_env_vars(t_prompt *prompt, char *argv[])
{
	char	*num;
	char	*value;

	value = getcwd(NULL, 0);
	custom_setenv("PWD", value, prompt);
	free(value);
	value = custom_getenv("SHLVL", prompt);
	if (!value || ft_atoi(value) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(value) + 1);
	if (num == NULL)
		terminate(ERR_MEM, 1);
	free(value);
	custom_setenv("SHLVL", num, prompt);
	free(num);
	value = custom_getenv("PATH", prompt);
	if (!value)
		custom_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt);
	free(value);
	value = custom_getenv("_", prompt);
	if (!value)
		custom_setenv("_", argv[0], prompt);
	free(value);
}
