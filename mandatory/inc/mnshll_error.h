/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:08:10 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/11 18:06:40 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNSHLL_ERROR_H
# define MNSHLL_ERROR_H

/* Error messages & warnings*/
# define ERR_MSG			(char *)"\aError: "
# define ERR_ARGS			(char *)"Incorrect number of arguments, expected 0!"
# define ERR_QUOTES			"Opening quotes aren't properly closed"
# define ERR_SYNTAX			"-msh: Syntax error near unexpected token"
# define ERR_GETPWD			"Function error -> getpwd"
# define ERR_MEM			"Function error -> malloc"
# define ERR_SIG			"Function error -> sigaction"
# define ERR_TC_GET_ATTR	"Function error -> tcgetattr"
# define ERR_SIGADDSET		"Function error -> sigaddset"
# define ERR_DUP			"Function error -> dup"
# define ERR_PIPE			"Function error -> pipe"
# define ERR_FORK			"Function error -> fork"
# define ERR_WAIT			"Function error -> wait"
# define ERR_EXECVE			"Function error -> execve"
# define ERR_OPEN			"Function error -> open"
# define ERR_CLOSE			"Function error -> close"
# define ERR_UNLINK			"Function error -> unlink"
# define ERR_CHLD			"Core dump in child"
# define TMP_FILE_HEREDOC	"/tmp/heredoc"
# define ERR_MRC			(char *)"There was an error while reading.\n"

// ERROR_MESSAGES FOR BUILTINS
# define ERR_PWD			(char *)"pwd: too many arguments\a\n"
# define ERR_ENV			(char *)"No such file or directory\n"
# define ERR_EXP			(char *)": not a valid identifier\n"

// Error codes
# define CATCH_ALL			1
# define SHELL_MISUSE		2
# define CANNOT_EXEC_CMD	126
# define CMD_NOT_FOUND		127
# define INVALID_EXIT_ARG	128
# define TERMINATE_CTRL_C	130
# define TERMINATE_QUIT		131
# define OUT_OF_RANGE		255

void	terminate(char *s, int syserr);
void	ft_prompt_clear(t_prompt *prompt, char *str, int syserr);

#endif