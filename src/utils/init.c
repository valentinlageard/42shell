/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:05:34 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 16:36:49 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	shell->cmds = NULL;
	shell->env = wenvtoenv(envp);
	return (shell);
}
