/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/02 17:23:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_echo_args(t_cmd *cmd, int *i)
{
	int		print_new_line;
	uint	j;

	print_new_line = 1;
	while (cmd->args[*i] && ft_strncmp(cmd->args[*i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->args[*i][j] && cmd->args[*i][j] == 'n')
			j++;
		if (j == ft_strlen(cmd->args[*i]))
		{
			print_new_line = 0;
			(*i)++;
		}
		else
			break ;
	}
	return (print_new_line);
}

void	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		first_printable_arg;
	int		print_new_line;

	i = 1;
	print_new_line = check_echo_args(cmd, &i);
	first_printable_arg = i;
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
