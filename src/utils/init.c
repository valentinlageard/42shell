/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:05:34 by valentin          #+#    #+#             */
/*   Updated: 2021/01/20 17:42:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	shell->cmdgs = NULL;
	shell->env = wenvtoenv(envp);
	update_pwd(shell);
	return (shell);
}
