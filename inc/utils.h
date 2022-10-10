/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:30 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/10 18:08:41 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERR_ARGS			"Incorrect number of arguments, expected 0"
# define ERR_GETPWD			"Function error -> getpwd"
# define ERR_MEM			"Fuction error -> malloc"
# define ERR_SIG			"Function error -> sigaction"
# define ERR_TC_GET_ATTR	"Function error -> tcgetattr"
# define ERR_SIGADDSET		"Function error -> sigaddset"
# define ERR_FORK			"Function error -> fork"
# define ERR_WAIT			"Function error -> wait"

/* utils.c */

void	terminate(char *s, int system_error_flag);
void	init_shell(void);
void	print_dir(void);

#endif
