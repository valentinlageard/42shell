/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:21:04 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 17:29:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*new_fds(void)
{
	t_fds	*fds;

	if (!(fds = (t_fds *)malloc(sizeof(t_fds))))
		return (NULL);
	fds->parent_in = -1;
	fds->parent_out = -1;
	fds->cur_in = -1;
	fds->cur_out = -1;
	fds->cur_pipe[0] = -1;
	fds->cur_pipe[1] = -1;
	return (fds);
}

void	save_inout(t_fds *fds)
{
	fds->parent_in = dup(0);
	fds->parent_out = dup(1);
}

void	restore_inout(t_fds *fds)
{
	dup2(fds->parent_in, 0);
	dup2(fds->parent_out, 1);
	close(fds->parent_in);
	close(fds->parent_out);
}

void	set_pipe(t_fds *fds)
{
	pipe(fds->cur_pipe);
	fds->cur_in = fds->cur_pipe[0];
	fds->cur_out = fds->cur_pipe[1];
}
