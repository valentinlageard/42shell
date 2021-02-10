/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmdg_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:35:34 by valentin          #+#    #+#             */
/*   Updated: 2021/02/11 00:20:53 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_text(t_pstate *ps, t_shell *shell)
{
	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (!(ps->curcmd))
		ps->curcmd = new_main_cmd(ps->tmp, shell);
	else if ((appendrealloc_arg(ps->tmp->str, ps->curcmd)) < 0)
		return (0);
	return (1);
}

int	handle_pipe(t_pstate *ps)
{
	if (ps->curcmd && ps->curcmdg)
	{
		if (ps->tmp->next && tok_is_identifier(ps->tmp->next))
		{
			append_cmd(ps->curcmd, &(ps->curcmdg->cmds));
			ps->curcmd = NULL;
			return (1);
		}
	}
	pcustom_error("minishell: syntax error near pipe\n");
	return (0);
}

int	handle_input_redirection(t_pstate *ps)
{
	t_red	*new_in_redir;

	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (!(new_in_redir = new_red(ps->tmp->str, 0, 0)))
		return (0);
	append_red(new_in_redir, &(ps->curcmdg->redirs));
	return (1);
}

int	handle_output_redirection(t_pstate *ps)
{
	t_red	*new_out_redir;

	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (ps->tmp->type == outr)
	{
		if (!(new_out_redir = new_red(ps->tmp->str, 1, 0)))
			return (0);
	}
	else
	{
		if (!(new_out_redir = new_red(ps->tmp->str, 1, 1)))
			return (0);
	}
	append_red(new_out_redir, &(ps->curcmdg->redirs));
	return (1);
}
