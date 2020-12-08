/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:00:28 by valentin          #+#    #+#             */
/*   Updated: 2020/12/08 14:12:09 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(int status, t_shell *shell)
{
	free_cmds(shell->cmds);
	free_env(shell->env);
	free(shell);
	exit(status);
}

void	perror_exit(t_shell *shell)
{
	ft_printf(strerror(errno));
	shell_exit(EXIT_FAILURE, shell);
}
