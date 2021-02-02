/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:16:30 by valentin          #+#    #+#             */
/*   Updated: 2021/02/03 00:10:18 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (ft_strncmp(cmd->main, "exit", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_exit(cmd, shell);
	else if (ft_strncmp(cmd->main, "env", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_env(shell);
	else if (ft_strncmp(cmd->main, "unset", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_unset(cmd, shell);
	else if (ft_strncmp(cmd->main, "export", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_export(cmd, shell);
	else if (ft_strncmp(cmd->main, "pwd", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_pwd();
	else if (ft_strncmp(cmd->main, "echo", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_echo(cmd);
	else if (ft_strncmp(cmd->main, "cd", ft_strlen(cmd->main)) == 0)
		exit_code = builtin_cd(cmd, shell);
	else
		exit_code = 130;
	return (exit_code);
}

void	exec_bin(t_cmd *cmd, t_shell *shell)
{
	char	**wenv;

	wenv = envtowenv(shell->env);
	execve(cmd->main, cmd->args, wenv);
	pcustom_error("minishell: ");
	pcustom_error(cmd->args[0]);
	pcustom_error(": ");
	perrno();
	pcustom_error("\n");
	ft_free_words(wenv);
	exit_shell(EXIT_FAILURE, shell);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	u_char	exit_code;

	if (cmd->is_valid)
	{
		if (cmd->is_builtin)
		{
			exit_code = (u_char)exec_builtin(cmd, shell);
			exit_shell(exit_code, shell);
		}
		else
			exec_bin(cmd, shell);
	}
	else
		exit_shell(127, shell);
}
