/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/19 14:53:42 by valentin         ###   ########.fr       */
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

void	exec_bin(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**wenv;

	// TODO : BETTER ERROR / SIGNAL MANAGEMENT !
	pid = fork();
	if (pid == 0) // In the child process
	{
		// Execute the command
		ft_printf("-> Executing : %s\n", cmd->main);
		wenv = envtowenv(shell->env);
		execve(cmd->main, cmd->args, wenv);
		ft_free_words(wenv);
	}
	else if (pid > 0) // In the parent process
	{
		// Wait for the child process to finish and kill it
		waitpid(pid, &status, WUNTRACED);
		kill(pid, SIGTERM);
	}
}

void	exec(t_shell *shell)
{
	t_cmd	*curcmd;

	curcmd = shell->cmds;
	while (curcmd)
	{
		if (curcmd->is_valid)
		{
			if (curcmd->is_builtin)
				exec_builtin(curcmd, shell);
			else
				exec_bin(curcmd, shell);
		}
		curcmd = curcmd->next;
	}
	free_cmds(shell->cmds);
}
