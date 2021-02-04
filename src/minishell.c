/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2021/02/04 15:07:02 by valentin         ###   ########.fr       */
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
		ft_printf("#############BEGIN#############\n");
		ft_printf("==============================\nParsing cltoks...\n");
		shell->cltoks = parse_cltoks(line);
		cur_cltok = shell->cltoks;
		ft_printf("Parsed cltoks.\n");
		free(line);
		while (cur_cltok)
		{
			ft_printf("==============================\nParsing cmdg...\n");
			cmdg = parse_cmdg(cur_cltok->ltok, shell);
			ft_printf("Parsed cmdg.\n");
			shell->cmdg = cmdg;
			ft_printf("==============================\nExecuting cmdg...\n");
			exec(shell);
			free_cmdg(shell->cmdg);
			shell->cmdg = NULL;
			ft_printf("Executed cmdg.\n");
			cur_cltok = cur_cltok->next;
		}
		free_cltoks(shell->cltoks);
		shell->cltoks = NULL;
		ft_printf("##############END##############\n");
		prompt();
	}
	if (read == 0)
		ft_printf("exit\n");
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
