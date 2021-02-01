/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:41:34 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 19:48:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

/*
** ft_read_line
** Parameters :
** 		- int fd : the file descriptor of the file / stream to read
** 		- char **line_ptr : a string parameter output to store the line read
** Returns :
** 		- If successful, it returns 0 and **line points to an allocated string
** 		containing the read line with \n or EOF replaced by \0.
** 		- If unsuccessful, it returns -1, frees internally allocated memory and
** 		sets line to NULL.
** Notes :
** 		- ft_read_line reads the file / stream character by character but
** 		allocates BUFFER_SIZE by BUFFER_SIZE.
** 		- It returns whenever a \n or a EOF is encountered.
*/

// TODO : TO NORME !

int	read_line(int fd, char **line_ptr)
{
	char	*line;
	char	read_buffer;
	int		chunk_num;
	int		i;
	int		read_error;

	line = NULL;
	read_buffer = 0;
	chunk_num = 1;
	i = 0;
	read_error = 0;
	if (!(line = (char *)malloc(BUFFER_SIZE)))
		return (-1);
	while ((read_error = read(fd, &read_buffer, 1)) >= 0)
	{
		if (i > chunk_num * BUFFER_SIZE - 1)
		{
			chunk_num++;
			if (!(line = (char *)ft_realloc(line, BUFFER_SIZE * chunk_num)))
			{
				free(line);
				return (-1);
			}
		}
		if (read_buffer == '\n' || read_error == 0)
		{
			line[i] = '\0';
			break ;
		}
		else
			line[i] = read_buffer;
		i++;
	}
	if (read_error == -1)
	{
		free(line);
		return (errno);
	}
	*line_ptr = line;
	return (ft_strlen(line));
}
