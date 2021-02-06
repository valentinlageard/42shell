/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:00 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 14:47:03 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_fds *fds)
{
	fds->parent_in = -1;
	fds->parent_out = -1;
	fds->first = -1;
	fds->last = -1;
	fds->cur_in = -1;
	fds->cur_out = -1;
	fds->cur_pipe[0] = -1;
	fds->cur_pipe[1] = -1;
}

void	store_parent_inout(t_fds *fds)
{
	fds->parent_in = dup(0);
	fds->parent_out = dup(1);
}

void	restore_parent_inout(t_fds *fds)
{
	dup2(fds->parent_in, 0);
	dup2(fds->parent_out, 1);
	close(fds->parent_in);
	close(fds->parent_out);
}

void	error_close_fds(t_fds *fds)
{
	restore_parent_inout(fds);
	if (fds->first >= 0)
		close(fds->first);
	if (fds->last >= 0)
		close(fds->last);
}

void	set_pipe(t_fds *fds)
{
	pipe(fds->cur_pipe);
	fds->cur_in = fds->cur_pipe[0];
	fds->cur_out = fds->cur_pipe[1];
}

void	update_inout(t_cmd *cmd, t_fds *fds)
{
	restore_cur_in(0, fds);
	if (!(cmd->next))
		fds->cur_out = fds->last;
	else
		set_pipe(fds);
	restore_cur_out(1, fds);
}
