/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2020/11/30 14:49:23 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0) // In the child process
	{
		// Get the binary absolute path if it exists
		// Execute the command
		execve(cmd[0], cmd, NULL);
	}
	else if (pid > 0) // In the parent process
	{
		// Wait for the whild process to finish and kill it
		waitpid(pid, &status, WUNTRACED);
		kill(pid, SIGTERM);
	}
}
