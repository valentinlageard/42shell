/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:16:30 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 17:26:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	ft_printf("-> Executing : %s\n", cmd->main);
	if (ft_strncmp(cmd->main, "exit", ft_strlen(cmd->main)) == 0)
		builtin_exit(shell);
	if (ft_strncmp(cmd->main, "env", ft_strlen(cmd->main)) == 0)
		builtin_env(shell);
	if (ft_strncmp(cmd->main, "unset", ft_strlen(cmd->main)) == 0)
		builtin_unset(cmd, shell);
	if (ft_strncmp(cmd->main, "export", ft_strlen(cmd->main)) == 0)
		builtin_export(cmd, shell);
	if (ft_strncmp(cmd->main, "pwd", ft_strlen(cmd->main)) == 0)
		builtin_pwd(shell);
	if (ft_strncmp(cmd->main, "echo", ft_strlen(cmd->main)) == 0)
		builtin_echo(cmd);
	if (ft_strncmp(cmd->main, "cd", ft_strlen(cmd->main)) == 0)
		builtin_cd(cmd, shell);
}

void	exec_simple_builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd->is_valid)
		exec_builtin(cmd, shell);
}

void	exec_bin(t_cmd *cmd, t_shell *shell)
{
	char	**wenv;

	ft_printf("-> Executing : %s\n", cmd->main);
	wenv = envtowenv(shell->env);
	execve(cmd->main, cmd->args, wenv);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->is_valid && cmd->is_builtin)
	{
		exec_builtin(cmd, shell);
		shell_exit(EXIT_SUCCESS, shell);
	}
	else if (cmd->is_valid && !cmd->is_builtin)
		exec_bin(cmd, shell);
}
