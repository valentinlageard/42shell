/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmdg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:48:36 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 18:20:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pstate	*new_pstate(void)
{
	t_pstate	*pstate;

	if (!(pstate = (t_pstate *)malloc(sizeof(t_pstate))))
		return (NULL);
	pstate->tmp = NULL;
	pstate->curcmd = NULL;
	pstate->curcmdg = NULL;
	return (pstate);
}

t_cmdg		*manage_tok_to_cmdg_error(t_pstate *ps)
{
	if (ps)
	{
		if (ps->curcmdg)
			free_cmdg(ps->curcmdg);
		if (ps->curcmd)
			free_cmd(ps->curcmd);
		free(ps);
	}
	return (NULL);
}

void		update_cmdg(t_pstate *ps)
{
	append_cmd(ps->curcmd, &(ps->curcmdg->cmds));
	ps->curcmd = NULL;
}

int			handle_tok(t_pstate *ps, t_shell *shell)
{
	int	err;

	err = 1;
	if (tok_is_identifier(ps->tmp))
		err = handle_text(ps, shell);
	else if (ps->tmp->type == pip)
		err = handle_pipe(ps);
	else if (ps->tmp->type == inr)
		err = handle_input_redirection(ps);
	else if (ps->tmp->type == outr || ps->tmp->type == outrapp)
		err = handle_output_redirection(ps);
	return (err);
}

t_cmdg		*tok_to_cmdg(t_tok *ltok, t_shell *shell)
{
	t_pstate	*ps;
	t_cmdg		*cmdg;
	int			err;

	err = 1;
	ps = new_pstate();
	ps->tmp = ltok;
	while (ps->tmp)
	{
		if (!err)
			return (manage_tok_to_cmdg_error(ps));
		err = handle_tok(ps, shell);
		ps->tmp = ps->tmp->next;
	}
	if (!err)
		return (manage_tok_to_cmdg_error(ps));
	if (ps->curcmd && ps->curcmdg)
		update_cmdg(ps);
	cmdg = ps->curcmdg;
	free(ps);
	return (cmdg);
}
