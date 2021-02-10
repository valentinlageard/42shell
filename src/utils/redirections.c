/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:38:49 by valentin          #+#    #+#             */
/*   Updated: 2021/02/11 00:03:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*new_red(char *path, int is_out, int is_append)
{
	t_red	*redir;

	if (!(redir = (t_red *)malloc(sizeof(t_red))))
		return (NULL);
	if (!(redir->path = ft_strdup(path)))
	{
		free(redir);
		return (NULL);
	}
	redir->is_out = is_out;
	redir->is_append = is_append;
	redir->next = NULL;
	return (redir);
}

void	append_red(t_red *redir, t_red **redirs)
{
	t_red	*tmp;

	if (!(*redirs))
		*redirs = redir;
	else
	{
		tmp = *redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

void	free_reds(t_red *reds)
{
	t_red	*next;

	while (reds)
	{
		next = reds->next;
		free(reds->path);
		free(reds);
		reds = next;
	}
}

void	print_reds(t_red *reds)
{
	t_red	*tmp;

	if (!reds)
		ft_printf("\t\tEMPTY\n");
	else
	{
		tmp = reds;
		while (tmp)
		{
			ft_printf("\t\tred->PATH : %s | IS_APPEND : %i\n",
				tmp->path, tmp->is_append);
			tmp = tmp->next;
		}
	}
}
