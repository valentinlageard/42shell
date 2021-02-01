/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtputstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:55:27 by vlageard          #+#    #+#             */
/*   Updated: 2020/01/20 18:28:50 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rtputstr_fd(char *s, int fd)
{
	int	i;
	int	error;

	i = 0;
	while (s[i])
	{
		error = ft_rtputchar_fd(s[i], fd);
		i++;
		if (error < 0)
			break ;
	}
	return (error);
}
