/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 17:56:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*exec_cmdg_init(t_cmdg *curcmdg, t_shell *shell)
{
	t_fds	*fds;

	if (!(fds = new_fds()))
		perrno_exit(shell);
	store_parent_inout(fds);
	if (select_first(curcmdg, fds) < 0)
	{
		free(fds);
		return (NULL);
	}
	if (select_last(curcmdg, fds) < 0)
	{
		free(fds);
		return (NULL);
	}
	fds->cur_in = fds->first;
	return (fds);
}

int		cmd_is_simple_builtin(t_cmd *cmd, t_cmdg *cmdg)
{
	return (cmd == cmdg->cmds && !(cmd->next) && cmd->is_builtin);
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	*fds;
	t_cmd	*curcmd;
	int		ret;

	if ((fds = exec_cmdg_init(curcmdg, shell)))
	{
		curcmd = curcmdg->cmds;
		while (curcmd)
		{
			update_inout(curcmd, fds);
			if (cmd_is_simple_builtin(curcmd, curcmdg))
				exec_builtin(curcmd, shell);
			else
			{
				pid = fork();
				if (pid == 0)
					exec_cmd(curcmd, shell);
			}
			curcmd = curcmd->next;
		}
		restore_parent_inout(fds);
		waitpid(pid, &ret, WUNTRACED);
		free(fds);
	}
}

void	exec(t_shell *shell)
{
	t_cmdg	*curcmdg;

	curcmdg = shell->cmdgs;
	while (curcmdg)
	{
		exec_cmdg(curcmdg, shell);
		curcmdg = curcmdg->next;
	}
	free_cmdgs(shell->cmdgs);
}
