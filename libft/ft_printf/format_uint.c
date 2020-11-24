/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 22:51:48 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:49 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int		uint_get_str_size(t_format *format, char *u_str, int va_uint)
{
	int	str_size;
	int	u_slen;
	int	fw_pad;
	int p_pad;

	if (format->precision == 0 && va_uint == 0)
		u_slen = 0;
	else
		u_slen = ft_strlen(u_str);
	if (format->precision == -1)
		str_size = u_slen + ft_max(0, format->fieldwidth - u_slen);
	else
	{
		u_slen = ft_strlen(u_str);
		p_pad = ft_max(0, format->precision - u_slen);
		fw_pad = ft_max(0, format->fieldwidth - (p_pad + u_slen));
		str_size = u_slen + p_pad + fw_pad;
	}
	return (str_size);
}

char	*uint_fill_str_no_precision(char *str, t_format *format, char *u_str)
{
	int	pad;
	int	u_slen;

	u_slen = ft_strlen(u_str);
	pad = ft_max(0, format->fieldwidth - u_slen);
	if (format->fieldwidth_mode == 0)
		ft_memset((void *)str, 32, pad);
	else if (format->fieldwidth_mode == 1)
		ft_memset((void *)str, 48, pad);
	else
		ft_memset((void *)(str + u_slen), 32, pad);
	if (format->fieldwidth_mode != 2)
		ft_memcpy((void *)(str + pad), (void *)u_str, u_slen);
	else
		ft_memcpy((void *)str, (void *)u_str, u_slen);
	return (str);
}

char	*uint_fill_str_precision(char *str, t_format *format, char *u_str)
{
	int	fw_pad;
	int	p_pad;
	int	u_slen;

	u_slen = ft_strlen(u_str);
	p_pad = ft_max(0, format->precision - u_slen);
	fw_pad = ft_max(0, format->fieldwidth - (p_pad + u_slen));
	if (format->fieldwidth_mode != 2)
	{
		ft_memset((void *)str, 32, fw_pad);
		ft_memset((void *)(str + fw_pad), 48, p_pad);
		ft_memcpy((void *)(str + fw_pad + p_pad), (void *)u_str, u_slen);
	}
	else
	{
		ft_memset((void *)str, 48, p_pad);
		ft_memcpy((void *)(str + p_pad), (void *)u_str, u_slen);
		ft_memset((void *)(str + p_pad + u_slen), 32, fw_pad);
	}
	return (str);
}

char	*format_uint(t_format *format, va_list valist)
{
	int		va_uint;
	char	*u_str;
	int		str_size;
	char	*str;

	va_uint = va_arg(valist, unsigned int);
	if (format->precision == 0 && va_uint == 0)
		u_str = ft_strdup("");
	else
		u_str = ft_utoa(va_uint);
	if (!u_str)
		return (NULL);
	str_size = uint_get_str_size(format, u_str, va_uint);
	if (!(str = (char *)malloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	if (format->precision == -1)
		str = uint_fill_str_no_precision(str, format, u_str);
	else
		str = uint_fill_str_precision(str, format, u_str);
	str[str_size] = 0;
	free(u_str);
	return (str);
}
