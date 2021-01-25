/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 18:41:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdg	*parse(char *line, t_shell *shell)
{
	t_cmdg	*cmdgs;
	t_tok	*ltok;

	cmdgs = NULL;
	ltok = tokenize_quotes(line);
	ltok = tokenize_separators(ltok, ";", 3);
	ltok = tokenize_separators(ltok, "|", 4);
	ltok = tokenize_separators(ltok, "<", 5);
	// TODO : Add redirection outputs
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	ltok = tokenize_input_redirections(ltok);
	print_ltok(ltok);
	cmdgs = tok_to_cmdgs(ltok, shell);
	print_cmdgs(cmdgs);
	free_ltok(ltok);
	return (cmdgs);
}
