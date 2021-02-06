/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:36:55 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 17:37:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mng_read_err(int read_err, char **line)
{
	if (read_err < 0)
	{
		free(*line);
		*line = NULL;
		return (errno);
	}
	return (0);
}
