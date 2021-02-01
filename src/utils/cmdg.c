/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdg.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:11:00 by valentin          #+#    #+#             */
/*   Updated: 2021/02/01 19:50:44 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdg	*new_cmdg(void)
{
	t_cmdg	*cmdg;

	if (!(cmdg = (t_cmdg *)malloc(sizeof(t_cmdg))))
		return (NULL);
	cmdg->cmds = NULL;
	cmdg->in_redirs = NULL;
	cmdg->out_redirs = NULL;
	return (cmdg);
}

void	free_cmdg(t_cmdg *cmdg)
{
	if (cmdg)
	{
		free_cmds(cmdg->cmds);
		free_inrs(cmdg->in_redirs);
		free_outrs(cmdg->out_redirs);
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
		ft_printf("\tINPUT REDIRECTIONS :\n");
		print_inrs(cmdg->in_redirs);
		ft_printf("\tOUTPUT REDIRECTIONS :\n");
		print_outrs(cmdg->out_redirs);
		ft_printf("\tCMDS :\n");
		print_cmds(cmdg->cmds);
	}
}
