/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/26 23:20:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : When check for input and output is done before cmdg execution is implemented,
// maybe you just need to open the last entry ?

void	set_input(t_cmdg *curcmdg, t_fds *fds)
{
	int		input_fd;
	t_inr	*tmp;

	input_fd = -1;
	if (curcmdg->in_redirs)
	{
		tmp = curcmdg->in_redirs;
		while (tmp)
		{
			if (input_fd >= 0)
				close(input_fd);
			input_fd = open(tmp->path, O_RDONLY); // TODO : CHECK ERROR or before ?
			tmp = tmp->next;
		}
		fds->cur_in = input_fd;
	}
	else
		fds->cur_in = dup(fds->parent_in);
}

void	set_output(t_cmdg *curcmdg, t_fds *fds)
{
	int		output_fd;
	t_outr	*tmp;

	output_fd = -1;
	if (curcmdg->out_redirs)
	{
		tmp = curcmdg->out_redirs;
		while (tmp) 
		{
			if (output_fd >= 0)
				close(output_fd);
			// TODO : PROTECT !
			if (tmp->is_append)
				output_fd = open(tmp->path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
			else
				output_fd = open(tmp->path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
			tmp = tmp->next;
		}
		fds->cur_out = output_fd;
		ft_printf("Output path is opened\n");
	}
	else
		fds->cur_out = dup(fds->parent_out);
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	t_fds	*fds;
	t_cmd	*curcmd;

	fds = new_fds(); // TODO : ENOMEM PROTECT
	save_inout(fds); // TODO : CHECK ERRORS
	curcmd = curcmdg->cmds;
	set_input(curcmdg, fds); // CHECK ERRORS
	while (curcmd)
	{
		restore_cur_in(0, fds); // TODO : CHECK ERRORS
		if (!(curcmd->next)) // TODO : Insert output redirection
			set_output(curcmdg, fds); // TODO : CHECK ERRORS
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
