/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:23:20 by valentin          #+#    #+#             */
/*   Updated: 2021/01/08 16:43:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (!change_value_var("PWD", path, &shell->env))
		append_var(new_var("PWD", path), &shell->env);
	free(path);
	// TODO : check for errors (new_var allocation, ...)
}
