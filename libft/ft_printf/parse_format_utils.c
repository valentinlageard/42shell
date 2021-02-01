/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlageard <vlageard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:03:48 by vlageard          #+#    #+#             */
/*   Updated: 2020/07/24 17:42:04 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "../libft.h"

t_format	*create_format(void)
{
	t_format *new_format;

	if (!(new_format = (t_format *)malloc(sizeof(t_format))))
		return (NULL);
	new_format->conversion = 0;
	new_format->fieldwidth = 0;
	new_format->fieldwidth_mode = 0;
	new_format->precision = -1;
	return (new_format);
}

int			is_conversion(char c)
{
	return (ft_iscinstr(c, "cspdiuxX%"));
}
