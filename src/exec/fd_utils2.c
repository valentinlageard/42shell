/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:12 by valentin          #+#    #+#             */
/*   Updated: 2021/02/09 17:33:39 by valentin         ###   ########.fr       */
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

int		select_first(t_cmdg *cmdg, t_fds *fds)
{
	t_inr	*tmp;

	if (cmdg->in_redirs)
	{
		tmp = cmdg->in_redirs;
		while (tmp)
		{
			if (fds->first >= 0)
				close(fds->first);
			if ((fds->first = open(tmp->path, O_RDONLY)) < 0)
			{
				predir_error(tmp->path);
				return (-1);
			}
			tmp = tmp->next;
		}
	}
	else
		fds->first = dup(fds->parent_in);
	return (0);
}

int		select_last(t_cmdg *cmdg, t_fds *fds)
{
	int		flags;
	t_outr	*tmp;

	if (cmdg->out_redirs)
	{
		tmp = cmdg->out_redirs;
		while (tmp)
		{
			if (fds->last >= 0)
				close(fds->last);
			if (tmp->is_append)
				flags = O_WRONLY | O_CREAT | O_APPEND;
			else
				flags = O_WRONLY | O_CREAT | O_TRUNC;
			if ((fds->last = open(tmp->path, flags, S_IRWXU)) < 0)
			{
				predir_error(tmp->path);
				return (-1);
			}
			tmp = tmp->next;
		}
	}
	else
		fds->last = dup(fds->parent_out);
	return (0);
}
