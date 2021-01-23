/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/20 17:35:07 by valentin         ###   ########.fr       */
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
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	print_ltok(ltok);
	cmdgs = tok_to_cmdgs(ltok, shell);
	print_cmdgs(cmdgs);
	free_ltok(ltok);
	return (cmdgs);
}
