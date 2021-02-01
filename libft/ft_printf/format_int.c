/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:03:32 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:36 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int		int_get_str_size(t_format *format, char *i_s, int va_int)
{
	int	i_sl;
	int	p_p;
	int	fw_p;
	int	str_size;

	if (format->precision == 0 && va_int == 0)
		i_sl = 0;
	else
		i_sl = ft_strlen(i_s);
	if (format->precision == -1)
	{
		fw_p = ft_max(0, format->fieldwidth - i_sl);
		str_size = fw_p + i_sl;
	}
	else
	{
		if (i_s[0] == '-')
			p_p = ft_max(0, format->precision - i_sl + 1);
		else
			p_p = ft_max(0, format->precision - i_sl);
		fw_p = ft_max(0, format->fieldwidth - (p_p + i_sl));
		str_size = fw_p + p_p + i_sl;
	}
	return (str_size);
}

char	*int_fill_no_precision(char *str, t_format *format, char *i_s)
{
	int fw_p;
	int	i_sl;
	int	n;

	i_sl = ft_strlen(i_s);
	fw_p = ft_max(0, format->fieldwidth - i_sl);
	n = i_s[0] == '-' ? 1 : 0;
	if (format->fieldwidth_mode == 0)
	{
		ft_memset((void *)str, 32, fw_p);
		ft_memcpy((void *)(str + fw_p), (void *)i_s, i_sl);
	}
	else if (format->fieldwidth_mode == 1)
	{
		if (n)
			str[0] = '-';
		ft_memset((void *)(str + n), 48, fw_p);
		ft_memcpy((void *)(str + fw_p + n), (void *)(i_s + n), i_sl - n);
	}
	else
	{
		ft_memcpy((void *)str, (void *)i_s, i_sl);
		ft_memset((void *)(str + i_sl), 32, fw_p);
	}
	return (str);
}

char	*int_fill_precision(char *str, t_format *format, char *i_s, int i_sl)
{
	int	p_p;
	int	fw_p;
	int	n;

	n = i_s[0] == '-' ? 1 : 0;
	p_p = ft_max(0, format->precision - i_sl + n);
	fw_p = ft_max(0, format->fieldwidth - (p_p + i_sl));
	if (format->fieldwidth_mode != 2)
	{
		ft_memset((void *)str, 32, fw_p);
		if (n)
			str[fw_p] = '-';
		ft_memset((void *)(str + fw_p + n), 48, p_p);
		ft_memcpy((void *)(str + fw_p + n + p_p), (void *)(i_s + n), i_sl - n);
	}
	else
	{
		if (n)
			str[0] = '-';
		ft_memset((void *)(str + n), 48, p_p);
		ft_memcpy((void *)(str + n + p_p), (void *)(i_s + n), i_sl - n);
		ft_memset((void *)(str + p_p + i_sl), 32, fw_p);
	}
	return (str);
}

char	*format_int(t_format *format, va_list valist)
{
	char	*str;
	int		va_int;
	char	*i_s;
	int		str_size;

	va_int = va_arg(valist, int);
	if (format->precision == 0 && va_int == 0)
		i_s = ft_strdup("");
	else
		i_s = ft_itoa(va_int);
	if (!i_s)
		return (NULL);
	str_size = int_get_str_size(format, i_s, va_int);
	if (!(str = (char *)malloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	if (format->precision == -1)
		str = int_fill_no_precision(str, format, i_s);
	else
		str = int_fill_precision(str, format, i_s, ft_strlen(i_s));
	str[str_size] = 0;
	free(i_s);
	return (str);
}
