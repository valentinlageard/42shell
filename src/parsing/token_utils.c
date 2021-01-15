/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:19:28 by valentin          #+#    #+#             */
/*   Updated: 2021/01/15 17:18:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_tok	*new_tok(char *str, int type)
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

void print_tok(t_tok *tok)
{
	ft_printf("TOKEN : %p | STR : \"%s\" | TYPE : %i | NEXT : %p\n", tok, tok->str, tok->type, tok->next);
}

void print_ltok(t_tok *tok)
{
	t_tok	*tmp;

	ft_printf("TOKENS :\n");
	if (!tok)
		ft_printf("\tEMPTY\n");
	tmp = tok;
	while (tmp)
	{
		ft_printf("\t");
		print_tok(tmp);
		tmp = tmp->next;
	}
}
