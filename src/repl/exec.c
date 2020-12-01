/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2020/12/01 16:34:19 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_cmd **cmds, t_shell *shell)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (cmds[i])
	{
		pid = fork();
		if (pid == 0) // In the child process
		{
			// Get the binary absolute path if it exists
			// Execute the command
			ft_printf("-> Executing : %s\n", cmds[i]->cmd);
			execve(cmds[i]->cmd, cmds[i]->args, shell->env);
		}
		else if (pid > 0) // In the parent process
		{
			// Wait for the whild process to finish and kill it
			waitpid(pid, &status, WUNTRACED);
			kill(pid, SIGTERM);
		}
		i++;
	}
	// TODO : free cmds and everything it contains !
}
