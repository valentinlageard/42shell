/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:05:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/02 21:38:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}

int		builtin_export(t_cmd *cmd, t_shell *shell)
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
	return (0);
}

int		builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		delete_var(cmd->args[i], &(shell->env));
		i++;
	}
	return (0);
}
