/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:05:22 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 16:55:42 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell)
{
	print_env(shell->env);
}

void	builtin_export(t_shell *shell)
{
	// IF key exists, replace value by the new value.
	// If key doesn't exist, create new var
	// If value has no = symbol, fuck this shit.
}

void	builtin_exit(t_shell *shell)
{
	shell_exit(EXIT_SUCCESS, shell);
}
