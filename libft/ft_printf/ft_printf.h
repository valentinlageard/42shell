/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:19:25 by vlageard          #+#    #+#             */
/*   Updated: 2020/02/04 18:51:09 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

typedef struct	s_format
{
	char		conversion;
	int			fieldwidth;
	int			fieldwidth_mode;
	int			precision;
}				t_format;

char			*format_char(t_format *format, va_list valist, int *nullchar);
char			*format_hex(t_format *format, va_list valist);
char			*format_int(t_format *format, va_list valist);
char			*format_pointer(t_format *format, va_list valist);
char			*format_str(t_format *format, va_list valist);
char			*format_uint(t_format *format, va_list valist);
char			*format_percent(t_format *format);
char			*formatter(t_format *format, va_list valist, int *nullchar);
char			*parse_format(int *i, const char *fstr, va_list valist,
				int *nullchar);
int				format_is_valid(int i, const char *fstr);
int				ft_printf(const char *fstr, ...);
int				is_conversion(char c);
int				percent_check(int *i, const char *fstr);
t_format		*create_format();

#endif
