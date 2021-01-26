/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:55:46 by valentin          #+#    #+#             */
/*   Updated: 2021/01/26 18:58:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_outr	*new_outr(char *path, int is_append)
{
	t_outr	*out_redir;

	if (!(out_redir = (t_outr *)malloc(sizeof(t_outr))))
		return (NULL);
	if (!(out_redir->path = ft_strdup(path)))
	{
		free(out_redir);
		return (NULL);
	}
	out_redir->is_append = is_append;
	out_redir->next = NULL;
	return (out_redir);
}

void	append_outr(t_outr *out_redir, t_outr **out_redirs)
{
	t_outr	*tmp;

	if (!(*out_redirs))
		*out_redirs = out_redir;
	else
	{
		tmp = *out_redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = out_redir;
	}
}

void	free_outrs(t_outr *outrs)
{
	t_outr	*next;

	while (outrs)
	{
		next = outrs->next;
		free(outrs->path);
		free(outrs);
		outrs = next;
	}
}

void	print_outrs(t_outr *outrs)
{
	t_outr	*tmp;

	if (!outrs)
		ft_printf("\t\tEMPTY\n");
	else
	{
		tmp = outrs;
		while (tmp)
		{
			ft_printf("\t\toutr->PATH : %s | IS_APPEND : %i\n", tmp->path, tmp->is_append);
			tmp = tmp->next;
		}
	}
}
