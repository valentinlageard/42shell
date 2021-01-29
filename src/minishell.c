/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 14:33:36 by valentin         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp); // TODO : Check error and exit if any
	repl(shell);
	shell_exit(EXIT_SUCCESS, shell);
}
