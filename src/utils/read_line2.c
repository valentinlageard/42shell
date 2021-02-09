/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:36:55 by valentin          #+#    #+#             */
/*   Updated: 2021/02/09 20:48:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read	*new_read_state(void)
{
	t_read	*n_read_state;

	if (!(n_read_state = (t_read *)malloc(sizeof(t_read))))
		return (NULL);
	n_read_state->read_buffer = '\0';
	n_read_state->chunk_num = 1;
	n_read_state->i = 0;
	n_read_state->read_err = 0;
	n_read_state->line = NULL;
	return (n_read_state);
}

void	free_read_state(t_read **read_state)
{
	if (*read_state)
	{
		if ((*read_state)->line)
		{
			free((*read_state)->line);
			(*read_state)->line = NULL;
		}
		free(*read_state);
		*read_state = NULL;
	}
}

int		mng_read_err(t_read **rs)
{
	if ((*rs)->read_err < 0)
	{
		free((*rs)->line);
		(*rs)->line = NULL;
		return (errno);
	}
	return (0);
}

void	reinit_read_state(t_read **rs)
{
	(*rs)->i = 0;
	ft_bzero((*rs)->line, (*rs)->chunk_num * BUFFER_SIZE);
}
