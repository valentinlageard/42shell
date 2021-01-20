/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/20 16:17:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse(char *line, t_shell *shell)
{
	t_cmd	*cmds;
	t_cmdg	*cmdgs;
	t_tok	*ltok;

	cmds = NULL;
	ltok = tokenize_quotes(line);
	ltok = tokenize_separators(ltok, ";", 3);
	ltok = tokenize_separators(ltok, "|", 4);
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	print_ltok(ltok);
	cmds = tok_to_cmds(ltok, shell);
	ft_printf("OK 1\n");
	cmdgs = tok_to_cmdgs(ltok, shell);
	ft_printf("OK 2\n");
	print_cmdgs(cmdgs);
	ft_printf("OK 3\n");
	free_cmdgs(cmdgs);
	ft_printf("OK 4\n");
	free_ltok(ltok);
	return (cmds);
}
