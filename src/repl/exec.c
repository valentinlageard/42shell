/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2020/12/02 17:01:53 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
		builtin_exit(shell);
}

void	exec_bin(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	// TODO : BETTER ERROR / SIGNAL MANAGEMENT !
	pid = fork();
	if (pid == 0) // In the child process
	{
		// Execute the command
		ft_printf("-> Executing : %s\n", cmd->cmd);
		execve(cmd->cmd, cmd->args, shell->env);
	}
	else if (pid > 0) // In the parent process
	{
		// Wait for the child process to finish and kill it
		waitpid(pid, &status, WUNTRACED);
		kill(pid, SIGTERM);
	}
}

void	exec(t_cmd **cmds, t_shell *shell)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->is_valid)
		{
			if (cmds[i]->is_builtin)
				exec_builtin(cmds[i], shell);
			else
				exec_bin(cmds[i], shell);
		}
		i++;
	}
	free_cmds(cmds);
}
