/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cltoks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:03:53 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 20:07:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cltok	*manage_cltok_syntax_error(t_tok **cur_ltok, t_cltok **cltoks)
{
	pcustom_error("minishell: syntax error\n");
	free_ltok(cur_ltok);
	free_cltoks(cltoks);
	return (NULL);
}

t_cltok	*get_cltoks(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*cur_ltok;
	t_cltok	*cltoks;

	tmp = ltok;
	cur_ltok = NULL;
	cltoks = NULL;
	while (tmp)
	{
		if (tmp->type == sep)
		{
			if (cur_ltok)
			{
				append_cltok(new_cltok(cur_ltok), &cltoks);
				cur_ltok = NULL;
			}
			else
				return (manage_cltok_syntax_error(&cur_ltok, &cltoks));
		}
		else
			append_tok(new_tok(tmp->str, tmp->type), &cur_ltok);
		tmp = tmp->next;
	}
	append_cltok(new_cltok(cur_ltok), &cltoks);
	return (cltoks);
}

t_cltok	*parse_cltoks(char *line)
{
	t_tok	*ltok;
	t_cltok	*cltoks;

	cltoks = NULL;
	ltok = tokenize_quotes(line);
	ltok = tokenize_separators(ltok, ";", sep);
	cltoks = get_cltoks(ltok);
	free_ltok(&ltok);
	if (!cltoks || !cltoks->ltok)
	{
		free(cltoks);
		return (NULL);
	}
	return (cltoks);
}
