/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/10 19:18:21 by valentin         ###   ########.fr       */
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

int		builtin_echo(t_cmd *cmd)
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
	return (0);
}

int		is_arg_digit(char *str)
{
	int	i;

	if (!(ft_isdigit(str[0]) || str[0] == '-'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int		builtin_exit(t_cmd *cmd, t_shell *shell)
{
	u_char	exit_code;
	uint	args_num;

	args_num = ft_wlen(cmd->args);
	exit_code = 0;
	pcustom_error("exit\n");
	if (args_num == 1)
		exit_shell(shell->exit_code, shell);
	if (args_num > 2)
		pcustom_error("minishell: exit: too many arguments\n");
	else if (args_num == 2)
	{
		if (!(is_arg_digit(cmd->args[1])))
		{
			pcustom_error("minishell: exit: ");
			pcustom_error(cmd->args[1]);
			pcustom_error(": numeric argument required\n");
			exit_code = 2;
		}
		else
			exit_code = (u_char)ft_atoi(cmd->args[1]);
		exit_shell(exit_code, shell);
	}
	return (1);
}
