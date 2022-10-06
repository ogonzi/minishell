/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogonzale <ogonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:58:30 by ogonzale          #+#    #+#             */
/*   Updated: 2022/10/06 18:01:47 by ogonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ERR_ARGS		"Incorrect number of arguments, expected 0"
# define ERR_GETPWD		"Function error -> getpwd"
# define ERR_MEM		"Fuction error -> malloc"
# define ERR_SIG		"Function error -> signal"

/* utils.c */

void	terminate(char *s, int system_error_flag);

#endif
