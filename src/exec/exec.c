/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/31 17:29:11 by valentin         ###   ########.fr       */
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

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	fds;
	t_cmd	*curcmd;
	int		status;

	status = 0;
	if ((setup_fds(&fds, curcmdg)) == 0)
	{
		curcmd = curcmdg->cmds;
		while (curcmd)
		{
			update_inout(curcmd, &fds);
			pid = fork();
			if (pid == 0)
				exec_cmd(curcmd, shell);
			curcmd = curcmd->next;
		}
		restore_parent_inout(&fds);
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
	}
}

void	exec(t_shell *shell)
{
	if (!(cmdg_has_unique_builtin(shell->cmdg)))
		exec_cmdg(shell->cmdg, shell);
	else
	{
		exec_unique_builtin(shell->cmdg, shell);
		shell->exit_code = 0; // TODO : get exit code based on success or failure of builtin
	}
	ft_printf("EXIT CODE : %d\n", shell->exit_code);
	free_cmdg(shell->cmdg);
}
