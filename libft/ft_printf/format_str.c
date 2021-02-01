/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:58:16 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:45 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int		str_get_str_size(t_format *format, char *va_str)
{
	int	str_size;
	int	va_strlen;

	if (!va_str)
	{
		if (format->precision >= 6 || format->precision == -1)
			va_strlen = 6;
		else
			va_strlen = format->precision;
	}
	else
		va_strlen = ft_strlen(va_str);
	if (format->precision == -1)
	{
		str_size = va_strlen + ft_max(0, format->fieldwidth - va_strlen);
	}
	else
	{
		str_size = ft_min(va_strlen, format->precision) +
		ft_max(0, format->fieldwidth - ft_min(va_strlen, format->precision));
	}
	return (str_size);
}

char	*str_fill_str(char *str, t_format *format, char *va_str)
{
	int	crop;
	int	pad;
	int	va_strlen;

	if (!va_str)
		va_strlen = 0;
	else
		va_strlen = ft_strlen(va_str);
	crop = format->precision == -1 ?
	(int)va_strlen :
	ft_min(va_strlen, format->precision);
	pad = ft_max(0, format->fieldwidth - crop);
	if (format->fieldwidth_mode == 2)
	{
		ft_memcpy((void *)str, (void *)va_str, crop);
		ft_memset((void *)(str + crop), 32, pad);
	}
	else
	{
		ft_memset((void *)str, 32, pad);
		ft_memcpy((void *)(str + pad), (void *)va_str, crop);
	}
	return (str);
}

char	*str_fill_null(char *str, t_format *format)
{
	int		pad;
	char	*null;
	int		va_strlen;

	if (format->precision >= 6 || format->precision == -1)
		va_strlen = 6;
	else
		va_strlen = format->precision;
	pad = ft_max(0, format->fieldwidth - va_strlen);
	null = ft_strdup("(null)");
	if (format->fieldwidth_mode != 2)
	{
		ft_memset((void *)str, 32, pad);
		ft_memcpy((void *)(str + pad), (void *)null, va_strlen);
	}
	else
	{
		ft_memcpy((void *)str, (void *)null, va_strlen);
		ft_memset((void *)(str + va_strlen), 32, pad);
	}
	free(null);
	return (str);
}

char	*format_str(t_format *format, va_list valist)
{
	char	*str;
	char	*va_str;
	int		str_size;

	va_str = va_arg(valist, char *);
	if (format->precision < -1)
		format->precision = -1;
	str_size = str_get_str_size(format, va_str);
	if (!(str = (char *)malloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	if (!va_str)
		str = str_fill_null(str, format);
	else
		str = str_fill_str(str, format, va_str);
	str[str_size] = 0;
	return (str);
}
