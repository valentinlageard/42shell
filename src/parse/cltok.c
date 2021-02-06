/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cltok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:04:44 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 16:30:47 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cltok	*new_cltok(t_tok *ltok)
{
	t_cltok	*ncltok;

	if (!(ncltok = (t_cltok *)malloc(sizeof(t_cltok))))
		return (NULL);
	ncltok->ltok = ltok;
	ncltok->next = NULL;
	return (ncltok);
}

void	free_cltok(t_cltok *cltok)
{
	if (cltok->ltok)
	{
		free_ltok(cltok->ltok);
		cltok->ltok = NULL;
	}
	free(cltok);
}

void	free_cltoks(t_cltok *cltoks)
{
	t_cltok	*tmp;
	t_cltok	*next;

	tmp = cltoks;
	while (tmp)
	{
		next = tmp->next;
		free_cltok(tmp);
		tmp = next;
	}
}

void	shallow_free_cloks(t_cltok *cltoks)
{
	t_cltok	*tmp;
	t_cltok	*next;

	tmp = cltoks;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

int		append_cltok(t_cltok *cltok, t_cltok **cltoks)
{
	t_cltok	*tmp;

	if (!cltok)
		return (-1);
	if (!(*cltoks))
		*cltoks = cltok;
	else
	{
		tmp = *cltoks;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cltok;
	}
	return (0);
}
