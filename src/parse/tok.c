/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:48:48 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 16:37:27 by valentin         ###   ########.fr       */
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
	tok->is_fchar_sp = 1;
	tok->is_lchar_sp = 1;
	tok->next_was_quote = 0;
	tok->next = NULL;
	return (tok);
}

void	free_tok(t_tok **tok)
{
	t_tok	*tmp;

	if (*tok)
	{
		tmp = *tok;
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		*tok = NULL;
	}
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

void	free_ltok(t_tok **ltok)
{
	t_tok	*tmp;
	t_tok	*next;

	if (*ltok)
	{
		tmp = *ltok;
		while (tmp)
		{
			next = tmp->next;
			free_tok(&tmp);
			tmp = next;
		}
		*ltok = NULL;
	}
}

t_tok	*copy_ltok(t_tok *ltok)
{
	t_tok	*nltok;
	t_tok	*tmp;

	nltok = NULL;
	tmp = ltok;
	while (tmp)
	{
		append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	return (nltok);
}
