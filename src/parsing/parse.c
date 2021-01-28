/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/28 14:49:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tokenize_line(char *line, t_shell *shell)
{
	t_tok	*ltok;

	ltok = tokenize_quotes(line);
	ltok = tokenize_separators(ltok, ";", 3);
	ltok = tokenize_separators(ltok, "|", 4);
	ltok = tokenize_separators(ltok, "<", 5);
	ltok = tokenize_separators(ltok, ">>", 7);
	ltok = tokenize_separators(ltok, ">", 6);
	// TODO : Add redirection outputs
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	ltok = tokenize_redirections(ltok);
	print_ltok(ltok);
	return (ltok);
}

t_cmdg	*parse(char *line, t_shell *shell)
{
	t_tok	*ltok;
	t_cmdg	*cmdgs;

	cmdgs = NULL;
	ltok = tokenize_line(line, shell);
	cmdgs = tok_to_cmdgs(ltok, shell);
	print_cmdgs(cmdgs);
	free_ltok(ltok);
	return (cmdgs);
}
