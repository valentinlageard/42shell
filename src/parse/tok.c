/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:48:48 by valentin          #+#    #+#             */
/*   Updated: 2021/01/31 18:33:36 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*new_tok(char *str, t_tok_type type)
{
	t_tok	*tok;

	if (!str)
		return (NULL);
	if (!(tok = (t_tok *)malloc(sizeof(t_tok))))
		return (NULL);
	if (!(tok->str = ft_strdup(str)))
	{
		free(tok);
		return (NULL);
	}
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	free_tok(t_tok *tok)
{
	free(tok->str);
	free(tok);
	tok = NULL;
}

int		append_tok(t_tok *tok, t_tok **ltok)
{
	t_tok	*tmp;

	if (!tok)
		return (-1);
	if (!(*ltok))
		*ltok = tok;
	else
	{
		tmp = *ltok;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
	}
	return (0);
}

void	free_ltok(t_tok *tok)
{
	t_tok	*next;

	while (tok)
	{
		next = tok->next;
		free_tok(tok);
		tok = next;
	}
}
