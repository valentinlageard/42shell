/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 00:59:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setup_fds(t_fds *fds, t_cmdg *curcmdg)
{
	init_fds(fds);
	store_parent_inout(fds);
	if (select_first(curcmdg, fds) < 0)
		return (-1);
	if (select_last(curcmdg, fds) < 0)
		return (-1);
	fds->cur_in = fds->first;
	return (0);
}

void	exec_unique_builtin(t_cmdg *cmdg, t_shell *shell)
{
	t_fds	fds;
	t_cmd	*curcmd;

	if ((setup_fds(&fds, cmdg)) == 0)
	{
		curcmd = cmdg->cmds;
		update_inout(curcmd, &fds);
		exec_builtin(curcmd, shell);
		restore_parent_inout(&fds);
	}
}

void	wait_and_process_children(t_cmdg *cmdg, t_shell *shell)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	status = 0;
	while ((pid = waitpid(-1, &status, WUNTRACED)) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 127)
			{
				cmd = get_corresponding_cmd(pid, shell->lpids, cmdg->cmds);
				perror_command_not_found(cmd);
			}
			if (pid == get_last_pid(shell->lpids))
				shell->exit_code = WEXITSTATUS(status);
		}
	}
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	fds;
	t_cmd	*curcmd;

	if ((setup_fds(&fds, curcmdg)) == 0)
	{
		curcmd = curcmdg->cmds;
		while (curcmd)
		{
			update_inout(curcmd, &fds);
			pid = fork();
			if (pid > 0)
				append_lpid(new_lpid(pid), &(shell->lpids));
			if (pid == 0)
				exec_cmd(curcmd, shell);
			curcmd = curcmd->next;
		}
		restore_parent_inout(&fds);
		wait_and_process_children(curcmdg, shell);
		free_lpids(shell->lpids);
		shell->lpids = NULL;
	}
}

void	exec(t_shell *shell)
{
	ft_printf("--------BEGIN-EXECUTION--------\n");
	if (!(cmdg_has_unique_builtin(shell->cmdg)))
		exec_cmdg(shell->cmdg, shell);
	else
	{
		exec_unique_builtin(shell->cmdg, shell);
		shell->exit_code = 0; // TODO : get exit code based on success or failure of builtin
	}
	ft_printf("---------END-EXECUTION---------\n");
	ft_printf("EXIT CODE : %d\n", shell->exit_code);
	free_cmdg(shell->cmdg);
}
