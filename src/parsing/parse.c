/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/18 14:32:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**parse(char *line, t_shell *shell)
{
	t_cmd	**cmds;
	t_tok	*ltok;

	cmds = NULL;
	ltok = tokenize_quotes(line);
	ltok = tokenize_separators(ltok);
	expand_vars(ltok, shell);
	ltok = tokenize_spaces(ltok);
	ft_printf("PARSED TOKENS :\n");
	print_ltok(ltok);
	cmds = tok_to_cmds(ltok, shell);
	free_ltok(ltok);
	return (cmds);
}
