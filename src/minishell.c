/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 14:53:52 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_read_error(int read)
{
	if (read == 0)
		pcustom_error("exit\n");
	if (read < 0)
	{
		pcustom_error("minishell: ");
		perrno();
		pcustom_error("\n");
		return (-1);
	}
	return (0);
}

int	repl(t_shell *shell)
{
	t_cltok	*cur_cltok;
	int		read;
	char	*line;

	read = 0;
	line = NULL;
	prompt();
	while ((read = read_line(0, &line)) >= 0 && line)
	{
		shell->pass = 0;
		shell->cltoks = parse_cltoks(line);
		cur_cltok = shell->cltoks;
		free(line);
		while (cur_cltok)
		{
			if (!(shell->cmdg = parse_cmdg(cur_cltok->ltok, shell)))
				shell->pass = 1;
			if (!shell->pass)
				exec(shell);
			free_cmdg(shell->cmdg);
			shell->cmdg = NULL;
			cur_cltok = cur_cltok->next;
		}
		shallow_free_cloks(shell->cltoks);
		shell->cltoks = NULL;
		if (!shell->pass)
			prompt();
	}
	free(line);
	return (manage_read_error(read));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc == 1 && argv)
	{
		setup_signal_handling();
		if (!(shell = init_shell(envp)))
		{
			pcustom_error("minishell: initialization error\n");
			exit_shell(EXIT_FAILURE, shell);
		}
		g_shell = shell;
		if ((repl(shell) == 0))
			exit_shell(EXIT_SUCCESS, shell);
		else
			exit_shell(EXIT_FAILURE, shell);
	}
	pcustom_error("minishell: unknown arguments given\n");
	return (EXIT_FAILURE);
}
