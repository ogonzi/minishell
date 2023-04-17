/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:38:58 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/17 13:45:45 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_utils.h"
#include "mnshll_error.h"

void	read_banner(void)
{
	int		fd;
	char	*line;

	fd = open("./.stuff/banner.ans", O_RDONLY);
	if (fd == -1)
	{
		ft_print_error("Error opening banner file.\a\n", EXIT_FAILURE);
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		ft_delete(line);
		line = get_next_line(fd);
	}
	ft_delete(line);
	if (close(fd) < 0)
		ft_print_error("Error closing banner file\n\a", EXIT_FAILURE);
}
