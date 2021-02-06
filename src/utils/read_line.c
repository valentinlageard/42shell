/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:34 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 17:40:51 by valentin         ###   ########.fr       */
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

void	init_read_line(char *read_buffer, int *chunk_num, int *i, int *read_err)
{
	*read_buffer = 0;
	*chunk_num = 1;
	*i = 0;
	*read_err = 0;
}

int		mng_nl(int i, char read_buffer, char **line)
{
	if (read_buffer == '\n')
	{
		(*line)[i] = '\0';
		return (1);
	}
	return (0);
}

int		mng_eof(int i, int read_err, char **line)
{
	if (read_err == 0 && i == 0)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	return (0);
}

int		realloc_new_chunk(int i, int *chunk_num, char **line)
{
	size_t	new_size;
	size_t	old_size;

	if (i > *chunk_num * BUFFER_SIZE - 1)
	{
		old_size = BUFFER_SIZE * *chunk_num;
		(*chunk_num)++;
		new_size = BUFFER_SIZE * *chunk_num;
		if (!(*line = (char *)ft_realloc(*line, new_size, old_size)))
		{
			free(*line);
			return (errno);
		}
	}
	return (0);
}

int		read_line(int fd, char **line_ptr)
{
	char	*line;
	char	read_buffer;
	int		chunk_num;
	int		i;
	int		read_err;

	init_read_line(&read_buffer, &chunk_num, &i, &read_err);
	if (!(line = (char *)malloc(BUFFER_SIZE)))
		return (errno);
	while ((read_err = read(fd, &read_buffer, 1)) >= 0)
	{
		if ((realloc_new_chunk(i, &chunk_num, &line)) != 0)
			return (errno);
		if (mng_eof(i, read_err, &line) || mng_nl(i, read_buffer, &line))
			break ;
		else if (!(read_err == 0 && i != 0))
			line[i] = read_buffer;
		if (read_err == 0 && i != 0)
			continue ;
		i++;
	}
	if (mng_read_err(read_err, &line) != 0)
		return (errno);
	*line_ptr = line;
	return (i);
}
