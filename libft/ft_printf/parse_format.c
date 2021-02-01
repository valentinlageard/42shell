/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:04:06 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:42:08 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

void		parse_left_fieldwidth(int *i, const char *fstr, t_format *format,
	va_list valist)
{
	if (!ft_isdigit(fstr[*i]) && fstr[*i] != '*')
		return ;
	if (fstr[*i] == '0')
	{
		format->fieldwidth_mode = 1;
		(*i)++;
	}
	if (fstr[*i] == '*')
	{
		format->fieldwidth = va_arg(valist, int);
		if (format->fieldwidth < 0)
		{
			format->fieldwidth = ft_abs(format->fieldwidth);
			format->fieldwidth_mode = 2;
		}
		(*i)++;
	}
	else
	{
		format->fieldwidth = ft_atoi(fstr + *i);
		while (ft_isdigit(fstr[*i]) && fstr[*i])
			(*i)++;
	}
}

void		parse_right_fieldwidth(int *i, const char *fstr, t_format *format,
	va_list valist)
{
	if (fstr[*i] != '-')
		return ;
	(*i)++;
	if (!ft_isdigit(fstr[*i]) && fstr[*i] != '*')
	{
		format->fieldwidth = 0;
		return ;
	}
	format->fieldwidth_mode = 2;
	while (fstr[*i] == '0')
		(*i)++;
	if (fstr[*i] == '*')
	{
		format->fieldwidth = ft_abs(va_arg(valist, int));
		(*i)++;
	}
	else
	{
		format->fieldwidth = ft_atoi(fstr + *i);
		while (ft_isdigit(fstr[*i]) && fstr[*i])
			(*i)++;
	}
}

void		parse_precision(int *i, const char *fstr, t_format *format,
	va_list valist)
{
	if (fstr[*i] != '.')
		return ;
	(*i)++;
	if (!ft_isdigit(fstr[*i]) && fstr[*i] != '*')
	{
		format->precision = 0;
		return ;
	}
	if (fstr[*i] == '*')
	{
		format->precision = va_arg(valist, int);
		(*i)++;
	}
	else
	{
		format->precision = ft_atoi(fstr + *i);
		while (ft_isdigit(fstr[*i]) && fstr[*i])
			(*i)++;
	}
}

void		parse_conversion(int *i, const char *fstr, t_format *format)
{
	format->conversion = fstr[*i];
	(*i)++;
}

char		*parse_format(int *i, const char *fstr, va_list valist,
	int *nullchar)
{
	t_format	*format;
	char		*str;

	if (!(format = create_format()))
		return (NULL);
	parse_left_fieldwidth(i, fstr, format, valist);
	parse_right_fieldwidth(i, fstr, format, valist);
	parse_precision(i, fstr, format, valist);
	parse_conversion(i, fstr, format);
	str = formatter(format, valist, nullchar);
	free(format);
	return (str);
}
