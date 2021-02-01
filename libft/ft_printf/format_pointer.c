/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:11:07 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:41:42 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int		pointer_get_str_size(t_format *format, char *p_str, void *va_ptr)
{
	int	p_slen;
	int	p_pad;
	int	fw_pad;
	int	str_size;

	if (!va_ptr)
	{
		p_slen = 3;
		fw_pad = ft_max(0, format->fieldwidth - 3);
		return (p_slen + fw_pad);
	}
	else
		p_slen = ft_strlen(p_str);
	if (format->precision == -1)
	{
		fw_pad = ft_max(0, format->fieldwidth - (2 + p_slen));
		str_size = fw_pad + 2 + p_slen;
	}
	else
	{
		p_pad = ft_max(0, format->precision - p_slen);
		fw_pad = ft_max(0, format->fieldwidth - (2 + p_pad + p_slen));
		str_size = p_pad + fw_pad + 2 + p_slen;
	}
	return (str_size);
}

char	*ptr_fill_no_precision(char *str, t_format *format, char *p_str)
{
	int	p_slen;
	int	fw_pad;

	p_slen = ft_strlen(p_str);
	fw_pad = ft_max(0, format->fieldwidth - (2 + p_slen));
	if (format->fieldwidth_mode == 0)
	{
		ft_memset((void *)str, 32, fw_pad);
		ft_memcpy((void *)(str + fw_pad), (void *)"0x", 2);
		ft_memcpy((void *)(str + fw_pad + 2), (void *)p_str, p_slen);
	}
	else if (format->fieldwidth_mode == 1)
	{
		ft_memcpy((void *)str, (void *)"0x", 2);
		ft_memset((void *)(str + 2), 48, fw_pad);
		ft_memcpy((void *)(str + fw_pad + 2), (void *)p_str, p_slen);
	}
	else
	{
		ft_memcpy((void *)str, (void *)"0x", 2);
		ft_memcpy((void *)(str + 2), (void *)p_str, p_slen);
		ft_memset((void *)(str + 2 + p_slen), 32, fw_pad);
	}
	return (str);
}

char	*ptr_fill_precision(char *str, t_format *format, char *p_str)
{
	int	p_slen;
	int	p_pad;
	int	fw_pad;

	p_slen = ft_strlen(p_str);
	p_pad = ft_max(0, format->precision - p_slen);
	fw_pad = ft_max(0, format->fieldwidth - (2 + p_pad + p_slen));
	if (format->fieldwidth_mode != 2)
	{
		ft_memset((void *)str, 32, fw_pad);
		ft_memcpy((void *)(str + fw_pad), (void *)"0x", 2);
		ft_memset((void *)(str + fw_pad + 2), 48, p_pad);
		ft_memcpy((void *)(str + fw_pad + 2 + p_pad), (void *)p_str, p_slen);
	}
	else
	{
		ft_memcpy((void *)str, (void *)"0x", 2);
		ft_memset((void *)(str + 2), 48, p_pad);
		ft_memcpy((void *)(str + 2 + p_pad), (void *)p_str, p_slen);
		ft_memset((void *)(str + 2 + p_pad + p_slen), 32, fw_pad);
	}
	return (str);
}

char	*ptr_fill_nil(char *str, t_format *format)
{
	char	*nil;
	int		fw_pad;

	nil = ft_strdup("0x0");
	fw_pad = ft_max(0, format->fieldwidth - 3);
	if (format->fieldwidth_mode == 2)
	{
		ft_memcpy((void *)str, (void *)nil, 3);
		ft_memset((void *)(str + 3), 32, fw_pad);
	}
	else
	{
		ft_memset((void *)str, 32, fw_pad);
		ft_memcpy((void *)(str + fw_pad), (void *)nil, 3);
	}
	free(nil);
	return (str);
}

char	*format_pointer(t_format *format, va_list valist)
{
	int		str_size;
	void	*va_ptr;
	char	*p_str;
	char	*str;

	va_ptr = va_arg(valist, void *);
	if (!(p_str = ft_ultoabase((unsigned long)(va_ptr), "0123456789abcdef")))
		return (NULL);
	str_size = pointer_get_str_size(format, p_str, va_ptr);
	if (!(str = (char *)malloc(sizeof(char) * (str_size + 1))))
		return (NULL);
	if (!va_ptr)
		str = ptr_fill_nil(str, format);
	else if (format->precision == -1)
		str = ptr_fill_no_precision(str, format, p_str);
	else
		str = ptr_fill_precision(str, format, p_str);
	str[str_size] = 0;
	free(p_str);
	return (str);
}
