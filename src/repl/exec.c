/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 20:23:20 by vlageard         ###   ########.fr       */
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
	int		i;

	i = 0;
	while (shell->cmds[i])
	{
		if (shell->cmds[i]->is_valid)
		{
			if (shell->cmds[i]->is_builtin)
				exec_builtin(shell->cmds[i], shell);
			else
				exec_bin(shell->cmds[i], shell);
		}
		i++;
	}
	free_cmds(shell->cmds);
}
