/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmdg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:48:36 by valentin          #+#    #+#             */
/*   Updated: 2021/02/05 14:24:48 by valentin         ###   ########.fr       */
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

t_cmd	*new_main_cmd(t_tok *tok, t_shell *shell)
{
	t_cmd	*ncmd;
	char	**args;

	ncmd = new_cmd();
	if (!(args = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(args[0] = ft_strdup(tok->str)))
	{
		free_cmd(ncmd);
		ft_free_words(args);
		return (NULL);
	}
	args[1] = NULL;
	ncmd->args = args;
	if (!ft_strlen(args[0]))
		ncmd->is_valid = 0;
	if (is_builtin(args[0]))
	{
		if (!(ncmd->main = ft_strdup(args[0])))
		{
			free_cmd(ncmd);
			return (NULL);
		}
		ncmd->is_builtin = 1;
	}
	else
		ncmd->main = select_binpath(args[0], shell);
	if (!ncmd->main)
		ncmd->is_valid = 0;
	return (ncmd);
}

void	update_cmdg(t_pstate *ps)
{
	append_cmd(ps->curcmd, &(ps->curcmdg->cmds));
	ps->curcmd = NULL;
}

int	handle_text(t_pstate *ps, t_shell *shell)
{
	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (!(ps->curcmd))
		ps->curcmd = new_main_cmd(ps->tmp, shell);
	else
		appendrealloc_arg(ps->tmp->str, ps->curcmd);
	return (1);
}

int	handle_pipe(t_pstate *ps)
{
	if (ps->curcmd && ps->curcmdg)
	{
		append_cmd(ps->curcmd, &(ps->curcmdg->cmds));
		ps->curcmd = NULL;
		return (1);
	}
	else
	{
		pcustom_error("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
}

int	handle_input_redirection(t_pstate *ps)
{
	t_inr	*new_in_redir;

	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (!(new_in_redir = new_inr(ps->tmp->str)))
		return (0);
	append_inr(new_in_redir, &(ps->curcmdg->in_redirs));
	return (1);
}

int		handle_output_redirection(t_pstate *ps)
{
	t_outr	*new_out_redir;

	if (!(ps->curcmdg))
		ps->curcmdg = new_cmdg();
	if (ps->tmp->type == outr)
	{
		if (!(new_out_redir = new_outr(ps->tmp->str, 0)))
			return (0);
	}
	else
	{
		if (!(new_out_redir = new_outr(ps->tmp->str, 1)))
			return (0);
	}
	append_outr(new_out_redir, &(ps->curcmdg->out_redirs));
	return (1);
}

t_cmdg	*tok_to_cmdg(t_tok *ltok, t_shell *shell)
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
		{
			free(ps);
			return (NULL);
		}
		if (tok_is_identifier(ps->tmp))
			err = handle_text(ps, shell);
		else if (ps->tmp->type == pip)
			err = handle_pipe(ps);
		else if (ps->tmp->type == inr)
			err = handle_input_redirection(ps);
		else if (ps->tmp->type == outr || ps->tmp->type == outrapp)
			err = handle_output_redirection(ps);
		ps->tmp = ps->tmp->next;
	}
	if (!err)
	{
		free(ps);
		return (NULL);
	}
	if (ps->curcmd && ps->curcmdg)
		update_cmdg(ps);
	cmdg = ps->curcmdg;
	free(ps);
	return (cmdg);
}
