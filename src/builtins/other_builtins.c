/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:22 by valentin          #+#    #+#             */
/*   Updated: 2021/01/30 18:30:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
	{
		i = 2;
		nl = 0;
	}
	else
	{
		i = 1;
		nl = 1;
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		i++;
	}
	if (nl)
		ft_printf("\n");
}

void	builtin_exit(t_shell *shell)
{
	exit_shell(EXIT_SUCCESS, shell);
}
