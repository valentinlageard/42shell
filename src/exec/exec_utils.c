/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:32:13 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 21:01:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_is_simple_builtin(t_cmd *cmd, t_cmdg *cmdg)
{
	return (cmd == cmdg->cmds && !(cmd->next) && cmd->is_builtin);
}

int		check_cmds(t_cmdg *cmdg)
{
	t_cmd	*tmp;
	int		valid;

	valid = 1;
	tmp = cmdg->cmds;
	while (tmp)
	{
		if (!(tmp->is_valid))
		{
			if (valid)
				valid = 0;
			pcustom_error("minishell: ");
			pcustom_error((char *)(tmp->args[0]));
			pcustom_error(": command not found\n");
		}
		tmp = tmp->next;
	}
	return (valid);
}
