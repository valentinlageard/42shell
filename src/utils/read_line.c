/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:34 by valentin          #+#    #+#             */
/*   Updated: 2021/02/09 20:59:42 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/*
** read_line
** Parameters :
**		- int fd
**		- line_ptr
** Returns :
**		- < 0 and line is NULL : There was an error.
**		- 0 and *line_ptr is NULL : EOF while nothing in line
**		- 0 and *line_ptr is empty string : empty new line
**		- > 0 and *line_ptr is string : filled new line.
*/

void	init_read_line(t_read **rs)
{
	(*rs)->read_buffer = 0;
	(*rs)->chunk_num = 1;
	(*rs)->i = 0;
	(*rs)->read_err = 0;
	if ((*rs)->line)
		free((*rs)->line);
	(*rs)->line = NULL;
}

int		mng_nl(t_read **rs)
{
	if ((*rs)->read_buffer == '\n')
	{
		((*rs)->line)[(*rs)->i] = '\0';
		return (1);
	}
	return (0);
}

int		mng_eof(t_read **rs)
{
	if ((*rs)->read_err == 0 && (*rs)->i == 0)
	{
		free((*rs)->line);
		(*rs)->line = NULL;
		return (1);
	}
	return (0);
}

int		realloc_new_chunk(t_read **rs)
{
	size_t	new_sz;
	size_t	old_sz;

	if ((*rs)->i > (*rs)->chunk_num * BUFFER_SIZE - 1)
	{
		old_sz = BUFFER_SIZE * (*rs)->chunk_num;
		((*rs)->chunk_num)++;
		new_sz = BUFFER_SIZE * (*rs)->chunk_num;
		if (!((*rs)->line = (char *)ft_realloc((*rs)->line, new_sz, old_sz)))
		{
			free((*rs)->line);
			return (errno);
		}
	}
	return (0);
}

int		read_line(int fd, char **line_ptr, t_read *rs)
{
	init_read_line(&rs);
	if (!(rs->line = (char *)malloc(BUFFER_SIZE)))
		return (errno);
	while ((rs->read_err = read(fd, &(rs->read_buffer), 1)) >= 0)
	{
		if ((realloc_new_chunk(&rs) != 0))
			return (errno);
		if (mng_eof(&rs) || mng_nl(&rs))
			break ;
		else if (!(rs->read_err == 0 && rs->i != 0))
			(rs->line)[rs->i] = rs->read_buffer;
		if (rs->read_err == 0 && rs->i != 0)
			continue ;
		(rs->i)++;
	}
	if (mng_read_err(&rs) != 0)
		return (errno);
	*line_ptr = rs->line;
	return (rs->i);
}
