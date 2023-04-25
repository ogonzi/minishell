/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnshll_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpeset-c <cpeset-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:56:48 by cpeset-c          #+#    #+#             */
/*   Updated: 2023/04/25 16:00:27 by cpeset-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mnshll_parser.h"
#include "mnshll_words.h"
#include "mnshll_expand.h"
#include "mnshll_exec.h"
#include "mnshll_utils.h"
#include "mnshll_data.h"
#include "mnshll_error.h"

void	aux_handler_pipeline(t_prompt *prompt, int tmp_fd[2])
{
	if (close(tmp_fd[0]))
		ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
	if (close(tmp_fd[1]))
		ft_prompt_clear(prompt, ERR_CLOSE, EXIT_FAILURE);
}

t_bool	ft_isall_space(char *buf)
{
	int	i;
	int	buf_len;

	buf_len = ft_strlen(buf);
	i = -1;
	while (++i < buf_len)
	{
		if (!ft_isspace(buf[i]))
			return (FALSE);
	}
	return (TRUE);
}
