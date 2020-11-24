/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:57:57 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/29 19:46:39 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int		whole;
	double	decimal;
	size_t	i;
	size_t	len;

	i = 0;
	whole = ft_abs(ft_atoi(str));
	decimal = 0;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		i++;
	if (i != ft_strlen(str))
	{
		decimal = (double)ft_atoi(str + i);
		len = ft_strlen(str + i);
		while (len--)
			decimal /= 10;
	}
	return (((double)whole + decimal) * (str[0] == '-' ? -1 : 1));
}
