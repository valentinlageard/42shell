/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2020/12/01 16:30:29 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	int		read_error;
	char	*line;
	t_cmd	**cmds;

	line = NULL;
	// DEBUG : Print environment variables
	ft_printf("ENVIRONMENT VARTIABLES :\n");
	int i = 0;
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
	ft_printf("GETVAL TEST | KEY = PATH : %s\n", get_envval("PATH", shell));
	ft_printf("$> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		ft_printf("Parsing...\n");
		cmds = parse(line, shell);
		ft_printf("Parsing done.\n");
		ft_printf("Parsed commands :\n");
		print_cmds(cmds);
		ft_printf("Executing...\n");
		exec(cmds, shell);
		ft_printf("Executing done.\n");
		free(line);
		ft_printf("$> ");
	}
	// If read_error == -1
	// Exits properly
}
