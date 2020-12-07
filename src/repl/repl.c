/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 19:43:22 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	int		read_error;
	char	*line;

	line = NULL;
	// DEBUG : Print environment variables
	/*ft_printf("ENVIRONMENT VARTIABLES :\n");
	int i = 0;
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}*/
	ft_printf("$> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		ft_printf("Parsing...\n");
		shell->cmds = parse(line, shell);
		free(line);
		ft_printf("Parsing done.\n");
		ft_printf("Parsed commands :\n");
		print_cmds(shell->cmds);
		ft_printf("Executing...\n");
		exec(shell);
		ft_printf("Executing done.\n");
		ft_printf("$> ");
	}
	// If read_error == -1
}
