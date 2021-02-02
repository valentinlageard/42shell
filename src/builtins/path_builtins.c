/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:13:50 by valentin          #+#    #+#             */
/*   Updated: 2021/02/02 16:08:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_shell *shell)
{
	ft_printf("%s\n", get_envval("PWD", shell->env));
}

void	perror_cd(char *arg_str)
{
	pcustom_error("minishell: cd: ");
	pcustom_error(arg_str);
	pcustom_error(": ");
	perrno();
	pcustom_error("\n");
}

void	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	int		arg_n;
	char	*path;

	path = NULL;
	arg_n = ft_wlen(cmd->args);
	if (arg_n == 2)
		path = cmd->args[1];
	else if (arg_n == 1)
	{
		path = get_envval("HOME", shell->env);
		if (!path)
			pcustom_error("minishell: cd: $HOME was not found\n");
	}
	else
	{
		pcustom_error("minishell: cd: too many arguments\n");
		return ;
	}
	if (path)
	{
		if (chdir(path) < 0)
			perror_cd(path);
		update_pwd(shell);
	}
}
