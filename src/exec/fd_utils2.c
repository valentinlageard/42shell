/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:12 by valentin          #+#    #+#             */
/*   Updated: 2021/02/11 00:23:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_cur_in(int fd, t_fds *fds)
{
	dup2(fds->cur_in, fd);
	close(fds->cur_in);
}

void	restore_cur_out(int fd, t_fds *fds)
{
	dup2(fds->cur_out, fd);
	close(fds->cur_out);
}

void	predir_error(char *path)
{
	pcustom_error("minishell: ");
	pcustom_error(path);
	pcustom_error(": ");
	perrno();
	pcustom_error("\n");
}

int		open_redirs(t_red *redir, t_fds *fds)
{
	int		flags;

	if (!redir->is_out)
	{
		if ((fds->first = open(redir->path, O_RDONLY)) < 0)
		{
			predir_error(redir->path);
			return (-1);
		}
	}
	else
	{
		if (redir->is_append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		if ((fds->last = open(redir->path, flags, S_IRWXU)) < 0)
		{
			predir_error(redir->path);
			return (-1);
		}
	}
	return (0);
}

int		select_redirections(t_cmdg *cmdg, t_fds *fds)
{
	t_red	*tmp;

	if (cmdg->redirs)
	{
		tmp = cmdg->redirs;
		while (tmp)
		{
			if (!tmp->is_out && fds->first >= 0)
				close(fds->first);
			if (tmp->is_out && fds->last >= 0)
				close(fds->last);
			if (open_redirs(tmp, fds) < 0)
				return (-1);
			tmp = tmp->next;
		}
	}
	if (fds->first < 0)
		fds->first = dup(fds->parent_in);
	if (fds->last < 0)
		fds->last = dup(fds->parent_out);
	return (0);
}
