/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:47:02 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 19:59:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_shell->is_executing)
			write(2, "Quit (core dumped)\n", 19);
		else
			write(2, "\b\b  \b\b", 6);
	}
	if (signum == SIGINT)
	{
		//ft_printf("g_shell->line :%s\n");
		free(g_shell->line);
		g_shell->line = NULL;
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
