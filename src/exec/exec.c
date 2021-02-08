/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/02/07 22:36:42 by valentin         ###   ########.fr       */
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

int		exec_unique_builtin(t_cmdg *cmdg, t_shell *shell)
{
	int		exit_code;
	t_fds	fds;
	t_cmd	*curcmd;

	exit_code = 1;
	if ((setup_fds(&fds, cmdg)) == 0)
	{
		curcmd = cmdg->cmds;
		update_inout(curcmd, &fds);
		exit_code = exec_builtin(curcmd, shell);
		restore_parent_inout(&fds);
	}
	else
		error_close_fds(&fds);
	return (exit_code);
}

void	kill_all_children(t_lpid *lpids)
{
	t_lpid	*tmp;

	tmp = lpids;
	while (tmp)
	{
		kill(tmp->pid, SIGQUIT);
		tmp = tmp->next;
	}
	errno = 0;
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
			{
				shell->exit_code = WEXITSTATUS(status);
				kill_all_children(shell->lpids);
			}
		}
	}
	free_lpids(shell->lpids);
	shell->lpids = NULL;
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	fds;
	t_cmd	*curcmd;

	if ((setup_fds(&fds, curcmdg)) < 0 || !curcmdg->cmds)
	{
		error_close_fds(&fds);
		return ;
	}
	curcmd = curcmdg->cmds;
	while (curcmd)
	{
		update_inout(curcmd, &fds);
		if (is_prev_cmd_builtin(curcmd, curcmdg->cmds))
			waitpid(get_last_pid(shell->lpids), NULL, WUNTRACED);
		pid = fork();
		if (pid > 0)
			append_lpid(new_lpid(pid), &(shell->lpids));
		if (pid == 0)
			exec_cmd(curcmd, shell);
		curcmd = curcmd->next;
	}
	restore_parent_inout(&fds);
	wait_and_process_children(curcmdg, shell);
}

void	exec(t_shell *shell)
{
	u_char	exit_code;

	if (!shell->cmdg)
		return ;
	else if (!shell->cmdg->cmds &&
		(shell->cmdg->in_redirs || shell->cmdg->out_redirs))
		exec_cmdg(shell->cmdg, shell);
	else if (!(cmdg_has_unique_builtin(shell->cmdg)))
		exec_cmdg(shell->cmdg, shell);
	else
	{
		exit_code = (u_char)exec_unique_builtin(shell->cmdg, shell);
		shell->exit_code = exit_code;
	}
}
