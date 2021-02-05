/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2021/02/05 13:59:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	repl(t_shell *shell)
{
	t_cltok	*cur_cltok;
	int		read;
	char	*line;
	t_cmdg	*cmdg;

	read = 0;
	line = NULL;
	prompt();
	while ((read = read_line(0, &line)) >= 0 && line)
	{
		shell->cltoks = parse_cltoks(line);
		cur_cltok = shell->cltoks;
		ft_printf("Parsed cltoks.\n");
		free(line);
		while (cur_cltok && !shell->pass)
		{
			if (!(cmdg = parse_cmdg(cur_cltok->ltok, shell)))
				shell->pass = 1;
			shell->cmdg = cmdg;
			if (!shell->pass)
				exec(shell);
			free_cmdg(shell->cmdg);
			shell->cmdg = NULL;
			cur_cltok = cur_cltok->next;
		}
		shallow_free_cloks(shell->cltoks);
		shell->cltoks = NULL;
		shell->pass = 0;
		prompt();
	}
	if (read == 0)
		pcustom_error("exit\n");
	free(line);
	if (read < 0)
	{
		pcustom_error("minishell: ");
		perrno();
		pcustom_error("\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	setup_signal_handling();
	shell = init_shell(envp); // TODO : Check error and exit if any
	g_shell = shell;
	repl(shell);
	exit_shell(EXIT_SUCCESS, shell);
}
