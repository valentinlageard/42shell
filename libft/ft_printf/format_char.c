/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:57:50 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:22 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

char	*fill_char(char *str, t_format *format, unsigned char va_c)
{
	int	pad;

	pad = format->fieldwidth ? format->fieldwidth - 1 : 0;
	if (format->fieldwidth_mode == 2)
	{
		str[0] = va_c;
		ft_memset((void *)(str + 1), 32, pad);
	}
	else
	{
		ft_memset((void *)str, 32, pad);
		str[pad] = va_c;
	}
	return (str);
}

char	*fill_nullchar(char *str, t_format *format, int *nullchar)
{
	int	pad;

	pad = format->fieldwidth ? format->fieldwidth - 1 : 0;
	ft_memset((void *)str, 32, pad);
	if (format->fieldwidth_mode == 2)
		*nullchar = 2;
	else
		*nullchar = 1;
	return (str);
}

char	*format_char(t_format *format, va_list valist, int *nullchar)
{
	char	*str;
	char	va_c;
	int		pad;
	int		c_nonnull;

	va_c = (unsigned char)va_arg(valist, int);
	c_nonnull = va_c ? 1 : 0;
	pad = format->fieldwidth ? format->fieldwidth - 1 : 0;
	if (!(str = (char *)malloc(sizeof(char) * (pad + c_nonnull + 1))))
		return (NULL);
	if (va_c)
		str = fill_char(str, format, va_c);
	else
		str = fill_nullchar(str, format, nullchar);
	str[pad + c_nonnull] = 0;
	return (str);
}
