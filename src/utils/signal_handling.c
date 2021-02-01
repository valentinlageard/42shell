/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:47:02 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 15:29:15 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int signum)
{
	(void)signum;
	write(1, "\b\b  \b\b", 6);
}

void	setup_signal_handling(void)
{
	signal(SIGQUIT, handle_sigquit);
}
