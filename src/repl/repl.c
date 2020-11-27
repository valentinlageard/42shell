/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2020/11/27 18:54:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(void)
{
	int		read_error;
	char	*line;

	line = NULL;
	ft_printf("> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		// Parse the line : for now, create a dummy parse_line function that only splits for now
		// Evaluate the line
		free(line);
		ft_printf("> ");
	}
	// If read_error == -1
	// Exits properly
}
