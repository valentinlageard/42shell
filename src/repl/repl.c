/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2020/11/28 17:28:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(void)
{
	int		read_error;
	char	*line;
	char	**args; // To be replaced by a command list ?

	line = NULL;
	ft_printf("$> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		args = ft_split(line, " "); // Split by space
		exec_cmd(args);
		free(line);
		ft_free_words(args);
		ft_printf("$> ");
	}
	// If read_error == -1
	// Exits properly
}
