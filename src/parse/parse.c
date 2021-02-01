/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/31 19:50:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			append_cltok(new_cltok(cur_ltok), &cltoks);
			cur_ltok = NULL;
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
	free_ltok(ltok);
	return (cltoks);
}

t_tok	*tokenize_cmdg(t_tok *ltok, t_shell *shell)
{
	ltok = tokenize_separators(ltok, "|", pip);
	ltok = tokenize_separators(ltok, "<", inr);
	ltok = tokenize_separators(ltok, ">>", outrapp);
	ltok = tokenize_separators(ltok, ">", outr);
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	ltok = tokenize_redirections(ltok);
	return (ltok);
}

t_cmdg	*parse_cmdg(t_tok *ltok, t_shell *shell)
{
	t_tok	*fully_tokenized_ltok;
	t_cmdg	*cmdg;

	cmdg = NULL;
	fully_tokenized_ltok = tokenize_cmdg(ltok, shell);
	print_ltok(fully_tokenized_ltok);
	cmdg = tok_to_cmdg(fully_tokenized_ltok, shell);
	print_cmdg(cmdg);
	free_ltok(fully_tokenized_ltok);
	return (cmdg);
}
