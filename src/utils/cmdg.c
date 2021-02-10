/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:11:00 by valentin          #+#    #+#             */
/*   Updated: 2021/02/11 00:22:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdg	*new_cmdg(void)
{
	t_cmdg	*cmdg;

	if (!(cmdg = (t_cmdg *)malloc(sizeof(t_cmdg))))
		return (NULL);
	cmdg->cmds = NULL;
	cmdg->redirs = NULL;
	return (cmdg);
}

void	free_cmdg(t_cmdg *cmdg)
{
	if (cmdg)
	{
		free_cmds(cmdg->cmds);
		free_reds(cmdg->redirs);
		free(cmdg);
	}
	cmdg = NULL;
}

void	print_cmdg(t_cmdg *cmdg)
{
	if (!cmdg)
		ft_printf("CMDG [%p] : EMPTY\n", cmdg);
	else
	{
		ft_printf("CMDG [%p] : \n", cmdg);
		ft_printf("\tREDIRECTIONS :\n");
		print_reds(cmdg->redirs);
		ft_printf("\tCMDS :\n");
		print_cmds(cmdg->cmds);
	}
}
