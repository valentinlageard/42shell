/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:47:02 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 19:33:41 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	if (signum == SIGINT)
	{
		g_shell->exit_code = 128 + SIGINT;
		write(2, "\n$> ", 4); // TO CHANGE !
	}
	return ;
}

void	setup_signal_handling(void)
{
	signal(SIGQUIT, handle_signals);
	signal(SIGINT, handle_signals);
}
