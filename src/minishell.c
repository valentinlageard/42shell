/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2021/01/31 18:31:32 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	t_cltok	*cur_cltok;
	int		read_error;
	char	*line;
	t_cmdg	*cmdg;

	line = NULL;
	ft_printf("$> ");
	while ((read_error = ft_read_line(0, &line)) >= 0)
	{
		ft_printf("#############################\nParsing...\n");
		shell->cltoks = parse_cltoks(line);
		free(line);
		cur_cltok = shell->cltoks;
		while (cur_cltok)
		{
			cmdg = parse_cmdg(cur_cltok->ltok, shell);
			shell->cmdg = cmdg;
			exec(shell);
			cur_cltok = cur_cltok->next;
		}
		free_cltoks(shell->cltoks);
		ft_printf("$> ");
	}
	// If read_error == -1
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp); // TODO : Check error and exit if any
	repl(shell);
	exit_shell(EXIT_SUCCESS, shell);
}
