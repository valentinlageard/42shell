/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:34:27 by valentin          #+#    #+#             */
/*   Updated: 2021/01/26 18:53:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inr	*new_inr(char *path)
{
	t_inr	*in_redir;

	if (!(in_redir = (t_inr *)malloc(sizeof(t_inr))))
		return (NULL);
	if (!(in_redir->path = ft_strdup(path)))
	{
		free(in_redir);
		return (NULL);
	}
	in_redir->next = NULL;
	return (in_redir);
}

void	append_inr(t_inr *in_redir, t_inr **in_redirs)
{
	t_inr	*tmp;

	if (!(*in_redirs))
		*in_redirs = in_redir;
	else
	{
		tmp = *in_redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = in_redir;
	}
}

void	free_inrs(t_inr *inrs)
{
	t_inr	*next;

	while (inrs)
	{
		next = inrs->next;
		free(inrs->path);
		free(inrs);
		inrs = next;
	}
}

void	print_inrs(t_inr *inrs)
{
	t_inr	*tmp;

	if (!inrs)
		ft_printf("\t\tEMPTY\n");
	else
	{
		tmp = inrs;
		while (tmp)
		{
			ft_printf("\t\tINR->PATH : %s\n", tmp->path);
			tmp = tmp->next;
		}
	}
}
