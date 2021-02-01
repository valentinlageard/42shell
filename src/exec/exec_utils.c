/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:32:13 by valentin          #+#    #+#             */
/*   Updated: 2021/01/31 20:26:15 by valentin         ###   ########.fr       */
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
