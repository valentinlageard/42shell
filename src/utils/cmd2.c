/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:43:14 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 15:43:29 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_printf("\tCMD : %s [%p]\n", cmd->main, cmd);
	ft_printf("\tARGS :\n");
	while ((cmd->args)[i])
	{
		ft_printf("\t- args[%d] : %s\n", i, (cmd->args)[i]);
		i++;
	}
	ft_printf("\tIS_VALID : %d\n", cmd->is_valid);
	ft_printf("\tIS_BUILTIN : %d\n", cmd->is_builtin);
	ft_printf("\tNEXT : [%p]\n", cmd->next);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		ft_printf("\t---------------------------\n");
		print_cmd(tmp);
		tmp = tmp->next;
	}
}
