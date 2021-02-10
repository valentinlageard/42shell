/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:47:02 by valentin          #+#    #+#             */
/*   Updated: 2021/02/10 14:33:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_children(int sig, t_shell *shell)
{
	t_lpid	*tmp;

	tmp = shell->lpids;
	while (tmp)
	{
		kill(tmp->pid, sig);
		tmp = tmp->next;
	}
}

void	handle_signals(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_shell->is_executing)
		{
			kill_children(SIGQUIT, g_shell);
			write(2, "Quit (core dumped)\n", 19);
		}
		else
			write(2, "\b\b  \b\b", 6);
	}
	if (signum == SIGINT)
	{
		if (!(g_shell->is_executing))
			reinit_read_state(&(g_shell->read_state));
		else
			kill_children(SIGINT, g_shell);
		g_shell->pass = 1;
		g_shell->exit_code = 128 + SIGINT;
		write(2, "\n", 1);
		if (!(g_shell->is_executing))
			prompt();
	}
	return ;
}

void	setup_signal_handling(void)
{
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
}
