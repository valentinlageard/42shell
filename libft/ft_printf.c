/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:19:18 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:38:09 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

int	nullchar_case(char *str, int *nullchar, int *error)
{
	if (*nullchar == 1)
	{
		*error = ft_rtputstr_fd(str, 1);
		*error = ft_rtputchar_fd(0, 1);
	}
	else
	{
		*error = ft_rtputchar_fd(0, 1);
		*error = ft_rtputstr_fd(str, 1);
	}
	free(str);
	return (ft_strlen(str) + 1);
}

int	parse_fstr_and_print(int *i, const char *fstr, va_list valist, int *error)
{
	int		count;
	char	*str;
	int		nullchar;

	str = NULL;
	count = 0;
	nullchar = 0;
	if (format_is_valid(*i, fstr))
	{
		str = parse_format(i, fstr, valist, &nullchar);
		if (!str)
			return (-1);
		if (!nullchar)
		{
			count = ft_strlen(str);
			*error = ft_rtputstr_fd(str, 1);
			free(str);
		}
		else
			count = nullchar_case(str, &nullchar, error);
	}
	else
		*error = ft_rtputchar_fd('%', 1);
	return (count);
}

int	parse_fstr(const char *fstr, va_list valist)
{
	int		i;
	int		count;
	int		error;

	i = 0;
	count = 0;
	error = 0;
	while (fstr[i])
	{
		if (fstr[i] != '%')
		{
			error = ft_rtputchar_fd(fstr[i], 1);
			i++;
			count++;
		}
		else
		{
			i++;
			count += parse_fstr_and_print(&i, fstr, valist, &error);
		}
		if (error < 0)
			return (error);
	}
	return (count);
}

int	ft_printf(const char *fstr, ...)
{
	va_list	valist;
	int		count;

	count = 0;
	va_start(valist, fstr);
	count = parse_fstr(fstr, valist);
	va_end(valist);
	return (count);
}
