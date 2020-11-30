/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:55:58 by valentin          #+#    #+#             */
/*   Updated: 2020/11/30 17:30:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	int		read_error;
	char	*line;
	char	**args; // To be replaced by a command list ?

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
		args = ft_split(line, " "); // Split by space
		// DEBUG : Print binpath
		ft_printf("selected bpath : %s\n", select_binpath(args[0], shell));
		exec_cmd(args);
		free(line);
		ft_free_words(args);
		ft_printf("$> ");
	}
	// If read_error == -1
	// Exits properly
}
