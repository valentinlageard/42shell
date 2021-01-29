/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:05:22 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 14:51:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell)
{
	print_env(shell->env);
}

void	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**split;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_iscinstr('=', cmd->args[i]))
		{
			split = key_val_split(cmd->args[i]);
			if (!(change_value_var(split[0], split[1], &(shell->env))))
				append_var(new_var(split[0], split[1]), &(shell->env));
			ft_free_words(split);
		}
		i++;
	}
	// If value has no = symbol, fuck this shit.
}

void	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		delete_var(cmd->args[i], &(shell->env));
		i++;
	}
}