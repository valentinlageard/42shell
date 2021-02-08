/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:05:34 by valentin          #+#    #+#             */
/*   Updated: 2021/02/07 23:09:04 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	shell->line = NULL;
	shell->is_executing = 0;
	shell->cltoks = NULL;
	shell->cmdg = NULL;
	shell->lpids = NULL;
	shell->env = wenvtoenv(envp);
	shell->pass = 0;
	shell->exit_code = 0;
	update_pwd(shell);
	return (shell);
}
