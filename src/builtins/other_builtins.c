/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 22:53:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	first_printable_arg;
	int	print_new_line;

	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-n", 3) == 0)
	{
		first_printable_arg = 2;
		print_new_line = 0;
	}
	else
	{
		first_printable_arg = 1;
		print_new_line = 1;
	}
	i = first_printable_arg;
	while (cmd->args[i])
	{
		if (i != first_printable_arg)
			ft_printf(" ");
		ft_printf("%s", cmd->args[i]);
		i++;
	}
	if (print_new_line)
		ft_printf("\n");
}

void	builtin_exit(t_shell *shell)
{
	exit_shell(EXIT_SUCCESS, shell);
}
