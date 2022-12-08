/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42barce>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:51:36 by ogonzale          #+#    #+#             */
/*   Updated: 2022/12/08 23:26:24 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

int		handle_input(t_list **cmd_line);
void	print_list(t_list *lst);

int	main(int argc, char *argv[])
{
	t_list	*cmd_line;

	if (argc != 1)
		terminate(ERR_ARGS, 0);
	set_sigint_action();
	do_sigign(SIGQUIT);
	init_shell();
	cmd_line = NULL;
	while (1)
	{
		if (handle_input(&cmd_line) == -1)
			break ;
		print_list(cmd_line);
		if (cmd_line != NULL)
			free_cmd_line(&cmd_line);
	}
	(void)argv;
	return (0);
}

void	print_list(t_list *lst)
{
	t_list	*lst_cpy;
	t_list	*word_cpy;

	lst_cpy = lst;
	while (lst_cpy)
	{
		word_cpy = ((t_cmd_line_data *)lst_cpy->data)->word;
		printf("%s\n", ((t_cmd_line_data *)lst_cpy->data)->cmd);
		while (word_cpy)
		{
			printf("\t%s (%d)\n", ((t_token_data *)word_cpy->data)->word,
				((t_token_data *)word_cpy->data)->type);
			word_cpy = word_cpy->next;
		}
		lst_cpy = lst_cpy->next;
	}
	lst_cpy = 0;
}

int	handle_input(t_list **cmd_line)
{
	char	*buf;
	int		len_buf;
	int		err;

	buf = readline("msh> ");
	if (buf == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (-1);
	}
	len_buf = ft_strlen(buf);
	if (len_buf != 0)
	{
		add_history(buf);
		err = split_cmd_line(cmd_line, buf);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
		err = split_words(cmd_line);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
		err = expand_words(cmd_line);
		if (err != 0)
			return (free_and_return_error_code(&buf, err));
	}
	free(buf);
	buf = NULL;
	return (0);
}
