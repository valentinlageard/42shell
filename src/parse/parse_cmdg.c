/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:37 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 18:04:38 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	cmdg = tok_to_cmdg(fully_tokenized_ltok, shell);
	free_ltok(fully_tokenized_ltok);
	return (cmdg);
}
