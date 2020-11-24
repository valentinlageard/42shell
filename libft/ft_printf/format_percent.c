/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:52:09 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:39 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdlib.h>

char	*format_percent(t_format *format)
{
	char	*str;
	int		pad;
	char	*perc;

	perc = ft_strdup("%");
	pad = format->fieldwidth > 1 ? format->fieldwidth - 1 : 0;
	if (!(str = (char *)malloc(sizeof(char) * (pad + 1 + 1))))
		return (NULL);
	if (format->fieldwidth_mode != 2)
	{
		ft_memset((void *)str, 32, pad);
		ft_memcpy((void *)(str + pad), (void *)perc, 1);
	}
	else
	{
		ft_memcpy((void *)str, (void *)perc, 1);
		ft_memset((void *)(str + 1), 32, pad);
	}
	free(perc);
	str[pad + 1] = 0;
	return (str);
}
