/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:32:13 by valentin          #+#    #+#             */
/*   Updated: 2021/02/03 20:14:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmdg_has_unique_builtin(t_cmdg *cmdg)
{
	return (!(cmdg->cmds->next) && (cmdg->cmds->is_builtin));
}

void	perror_command_not_found(t_cmd *cmd)
{
	pcustom_error("minishell: ");
	pcustom_error(cmd->args[0]);
	pcustom_error(": command not found\n");
}

int		is_prev_cmd_builtin(t_cmd *cmd, t_cmd *cmds)
{
	t_cmd	*prev;
	t_cmd	*tmp;

	if (cmds)
	{
		prev = NULL;
		tmp = cmds;
		while (tmp)
		{
			if (tmp == cmd)
			{
				if (prev && prev->is_builtin)
					return (1);
				else
					return (0);
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0);
}
