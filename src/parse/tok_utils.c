/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:15:19 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 17:01:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tok_is_identifier(t_tok *tok)
{
	if (tok->type == txt || tok->type == squo || tok->type == dquo)
		return (1);
	else
		return (0);
}

void	print_tok(t_tok *tok)
{
	ft_printf("TOKEN : [%p] | STR : \"%s\" | TYPE : %i",
		tok, tok->str, tok->type);
	ft_printf(" | FCSP : %i | LCSP : %i",
		tok->is_fchar_sp, tok->is_lchar_sp);
	ft_printf(" | NWQ : %i | NEXT : [%p]\n",
		tok->next_was_quote, tok->next);
}

void	print_ltok(t_tok *tok)
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
