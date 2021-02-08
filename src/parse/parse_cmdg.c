/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmdg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:04:37 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 17:00:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tokenize_cmdg(t_tok *ltok, t_shell *shell)
{
	t_tok	*nltok;

	nltok = copy_ltok(ltok);
	nltok = tokenize_separators(nltok, "|", pip);
	nltok = tokenize_separators(nltok, "<", inr);
	nltok = tokenize_separators(nltok, ">>", outrapp);
	nltok = tokenize_separators(nltok, ">", outr);
	expand_vars(nltok, shell);
	ft_printf("BEFORE SPACE TOKENIZATION : \n");
	print_ltok(nltok);
	nltok = tokenize_spaces(nltok);
	ft_printf("BEFORE CONCATENATION : \n");
	print_ltok(nltok);
	nltok = concatenate_identifiers(nltok);
	ft_printf("AFTER CONCATENATION : \n");
	print_ltok(nltok);
	nltok = tokenize_redirections(nltok);
	return (nltok);
}

t_cmdg	*parse_cmdg(t_tok *ltok, t_shell *shell)
{
	t_tok	*fully_tokenized_ltok;
	t_cmdg	*cmdg;

	cmdg = NULL;
	fully_tokenized_ltok = tokenize_cmdg(ltok, shell);
	cmdg = tok_to_cmdg(fully_tokenized_ltok, shell);
	free_ltok(&fully_tokenized_ltok);
	return (cmdg);
}
