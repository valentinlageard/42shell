/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:13:50 by valentin          #+#    #+#             */
/*   Updated: 2021/02/02 16:31:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_shell *shell)
{
	char	*path;

	if ((path = getcwd(NULL, 0)))
	{
		if (!change_value_var("PWD", path, &shell->env))
			append_var(new_var("PWD", path), &shell->env);
		free(path);
	}
}

void	builtin_pwd(void)
{
	char	*path;

	if (!(path = getcwd(NULL, 0)))
		ft_printf("\n");
	else
	{
		ft_printf("%s\n", path);
		free(path);
	}
}

void	perror_cd(char *arg_str)
{
	pcustom_error("minishell: cd: ");
	pcustom_error(arg_str);
	pcustom_error(": ");
	perrno();
	pcustom_error("\n");
}

char	*get_cd_path(t_cmd *cmd, t_shell *shell)
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
		pcustom_error("minishell: cd: too many arguments\n");
	return (path);
}

void	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if ((path = get_cd_path(cmd, shell)))
	{
		if (chdir(path) < 0)
			perror_cd(path);
		update_pwd(shell);
	}
}
