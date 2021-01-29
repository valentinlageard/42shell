/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:15:19 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 15:17:13 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tok_is_identifier(t_tok *tok)
{
	if (tok->type == txt || tok->type == squo || tok->type == dquo)
		return (1);
	else
		return (0);
}

void print_tok(t_tok *tok)
{
	ft_printf("TOKEN : [%p] | STR : \"%s\" | TYPE : %i | NEXT : [%p]\n", tok, tok->str, tok->type, tok->next);
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
