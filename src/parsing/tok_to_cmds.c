/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:46:24 by valentin          #+#    #+#             */
/*   Updated: 2021/01/20 17:44:24 by valentin         ###   ########.fr       */
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
	pstate->cmdgs = NULL;
	return (pstate);
}

t_cmd	*new_main_cmd(t_tok *tok, t_shell *shell)
{
	t_cmd	*ncmd;
	char	**args;

	ncmd = new_cmd();
	if (!(args = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	args[0] = ft_strdup(tok->str);
	args[1] = NULL;
	ncmd->args = args;
	if (is_builtin(args[0]))
	{
		ncmd->main = ft_strdup(args[0]);
		ncmd->is_builtin = 1;
	}
	else
		ncmd->main = select_binpath(args[0], shell);
	if (!ncmd->main)
		ncmd->is_valid = 0;
	return (ncmd);
}

void	update_cmdgs(t_pstate *ps)
{
	append_cmd(ps->curcmd, &(ps->curcmdg->cmds));
	append_cmdg(ps->curcmdg, &(ps->cmdgs));
	ps->curcmd = NULL;
	ps->curcmdg = NULL;
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

int	handle_sep(t_pstate *ps)
{
	if (ps->curcmd && ps->curcmdg)
	{
		update_cmdgs(ps);
		return (1);
	}
	else
		return (0);
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
		return (0);
}

t_cmdg	*tok_to_cmdgs(t_tok *ltok, t_shell *shell)
{
	t_pstate	*ps;
	t_cmdg		*cmdgs;
	int			err;

	err = 1;
	ps = new_pstate();
	ps->tmp = ltok;
	while (ps->tmp)
	{
		if (!err)
			return (NULL);
		if (ps->tmp->type == 0 || ps->tmp->type == 1 || ps->tmp->type == 2)
			err = handle_text(ps, shell);
		else if (ps->tmp->type == 3)
			err = handle_sep(ps);
		else if (ps->tmp->type == 4)
			err = handle_pipe(ps);
		ps->tmp = ps->tmp->next;
	}
	if (ps->curcmd && ps->curcmdg)
		update_cmdgs(ps);
	cmdgs = ps->cmdgs;
	free(ps);
	return (cmdgs);
}
