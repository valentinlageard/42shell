/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:00:28 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 17:23:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(int status, t_shell *shell)
{
	free_cmdgs(shell->cmdgs);
	free_env(shell->env);
	free(shell);
	exit(status);
}

void	pcustom_error(char *str_error)
{
	ft_putstr_fd(str_error, 2);
}

void	perrno(void)
{
	ft_putstr_fd(strerror(errno), 2);
}

void	pcustom_error_exit(char *str_error, t_shell *shell)
{
	pcustom_error(str_error);
	exit_shell(EXIT_FAILURE, shell);
}

void	perrno_exit(t_shell *shell)
{
	perrno();
	exit_shell(EXIT_FAILURE, shell);
}
