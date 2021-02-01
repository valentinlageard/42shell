/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lpid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:26:30 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 19:43:32 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*new_lpid(pid_t pid)
{
	t_lpid	*lpid;

	if (!(lpid = (t_lpid *)malloc(sizeof(t_lpid))))
		return (NULL);
	lpid->pid = pid;
	lpid->next = NULL;
	return (lpid);
}

void	free_lpids(t_lpid *lpids)
{
	t_lpid	*tmp;
	t_lpid	*next;

	tmp = lpids;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	lpids = NULL;
}

int		append_lpid(t_lpid *lpid, t_lpid **lpids)
{
	t_lpid	*tmp;

	if (!(lpid))
		return (-1);
	if (!(*lpids))
		*lpids = lpid;
	else
	{
		tmp = *lpids;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lpid;
	}
	return (0);
}

pid_t	get_last_pid(t_lpid *lpids)
{
	t_lpid	*tmp;

	tmp = lpids;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->pid);
}

t_cmd	*get_corresponding_cmd(pid_t pid, t_lpid *lpids, t_cmd *cmds)
{
	t_lpid	*tmp_lpid;
	t_cmd	*tmp_cmd;

	tmp_lpid = lpids;
	tmp_cmd = cmds;
	while (tmp_lpid && tmp_lpid->pid != pid)
	{
		tmp_cmd = tmp_cmd->next;
		tmp_lpid = tmp_lpid->next;
	}
	return (tmp_cmd);
}
