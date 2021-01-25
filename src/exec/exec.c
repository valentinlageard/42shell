/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 18:50:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_initial_input(t_cmdg *curcmdg, t_fds *fds)
{
	if (curcmdg->in_redir)
		fds->cur_in = open(curcmdg->in_redir, O_RDONLY);
	else
		fds->cur_in = dup(fds->parent_in);
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	*fds;
	t_cmd	*curcmd;

	fds = new_fds(); // TODO : ENOMEM PROTECT
	save_inout(fds); // TODO : CHECK ERRORS
	curcmd = curcmdg->cmds;
	// TODO : Insert input redirection
	set_initial_input(curcmdg, fds); // CHECK ERRORS
	while (curcmd)
	{
		restore_cur_in(0, fds); // TODO : CHECK ERRORS
		if (!(curcmd->next)) // TODO : Insert output redirection
			fds->cur_out = dup(fds->parent_out); // TODO : CHECK ERRORS
		else
			set_pipe(fds); // TODO : CHECK ERRORS
		restore_cur_out(1, fds); // TODO : CHECK ERRORS
		pid = fork(); // TODO : CHECK ERRORS
		if (pid == 0)
			exec_cmd(curcmd, shell);
		curcmd = curcmd->next;
	}
	restore_inout(fds); // TODO : CHECK ERRORS
	waitpid(pid, NULL, WUNTRACED); // STATUS ?
	free(fds);
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
