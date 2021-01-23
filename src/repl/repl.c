/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/20 17:42:08 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	int		read_error;
	char	*line;

	line = NULL;
	ft_printf("$> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		ft_printf("Parsing...\n");
		shell->cmdgs = parse(line, shell);
		free(line);
		ft_printf("Parsing done.\n");
		ft_printf("Parsed commands :\n");
		ft_printf("Executing...\n");
		exec(shell);
		ft_printf("Executing done.\n");
		ft_printf("$> ");
	}
	// If read_error == -1
}
