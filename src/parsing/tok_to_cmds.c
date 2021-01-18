/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:46:24 by valentin          #+#    #+#             */
/*   Updated: 2021/01/18 14:33:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd	**tok_to_cmds(t_tok *ltok, t_shell *shell)
{
	t_tok	*tmp;
	t_cmd	*curcmd;
	t_cmd	**cmds;

	tmp = ltok;
	curcmd = NULL;
	cmds = NULL;
	while (tmp)
	{
		if ((tmp->type == 0 || tmp->type == 1 || tmp->type == 2) && !curcmd)
			curcmd = new_main_cmd(tmp, shell);
		else if ((tmp->type == 0 || tmp->type == 1 || tmp->type == 2) && curcmd)
			appendrealloc_arg(tmp->str, curcmd); // TODO : Check for error !
		else if (tmp->type == 3 && curcmd)
		{
			cmds = appendrealloc_cmd(curcmd, cmds);
			curcmd = NULL;
		}
		else if (tmp->type == 3 && !curcmd)
			ft_printf("Separator error\n");
		tmp = tmp->next;
	}
	if (curcmd)
		cmds = appendrealloc_cmd(curcmd, cmds);
	return (cmds);
}
