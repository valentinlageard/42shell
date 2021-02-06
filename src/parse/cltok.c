/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cltok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:04:44 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 20:43:12 by valentin         ###   ########.fr       */
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

void	free_cltok(t_cltok **cltok)
{
	t_cltok	*tmp;

	if (*cltok)
	{
		tmp = *cltok;
		if (tmp->ltok)
			free_ltok(&(tmp->ltok));
		free(*cltok);
		*cltok = NULL;
	}
}

void	free_cltoks(t_cltok **cltoks)
{
	t_cltok	*tmp;
	t_cltok	*next;

	if (*cltoks)
	{
		tmp = *cltoks;
		while (tmp)
		{
			next = tmp->next;
			free_cltok(&tmp);
			tmp = next;
		}
		*cltoks = NULL;
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
