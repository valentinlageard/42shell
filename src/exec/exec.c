/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 16:50:08 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*exec_cmdg_init(t_cmdg *curcmdg, t_shell *shell)
{
	t_fds	*fds;

	if (!(fds = new_fds()))
		perrno_exit(shell);
	store_parent_inout(fds); // TODO : CHECK ERRORS
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

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	*fds;
	t_cmd	*curcmd;

	if ((fds = exec_cmdg_init(curcmdg, shell)))
	{
		curcmd = curcmdg->cmds;
		while (curcmd)
		{
			restore_cur_in(0, fds); // TODO : CHECK ERRORS
			if (!(curcmd->next)) // TODO : Insert output redirection
			fds->cur_out = fds->last;
			else
			set_pipe(fds); // TODO : CHECK ERRORS
			restore_cur_out(1, fds); // TODO : CHECK ERRORS
			pid = fork(); // TODO : CHECK ERRORS
			if (pid == 0)
			exec_cmd(curcmd, shell);
			curcmd = curcmd->next;
		}
		restore_parent_inout(fds); // TODO : CHECK ERRORS
		waitpid(pid, NULL, WUNTRACED); // STATUS ?
		free(fds);
	}
}

void	exec(t_shell *shell)
{
	t_cmdg	*curcmdg;

	curcmdg = shell->cmdgs;
	while (curcmdg)
	{
		if (!(curcmdg->cmds->next) && (curcmdg->cmds->is_builtin))
		{
			ft_printf("Executing simple builtin\n");
			exec_simple_builtin(curcmdg->cmds, shell);
		}
		else
		{
			ft_printf("Executing command group\n");
			exec_cmdg(curcmdg, shell);
		}
		curcmdg = curcmdg->next;
	}
	free_cmdgs(shell->cmdgs);
}
