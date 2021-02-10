/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:05:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/10 20:42:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		ft_printf("c : %c\n", str[i]);
		if (!(ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int		builtin_env(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}

int		perror_env(char *arg)
{
	pcustom_error("minishell: export: `");
	pcustom_error(arg);
	pcustom_error("': not a valid identifier\n");
	return (1);
}

int		builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		error;
	char	**split;

	error = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_iscinstr('=', cmd->args[i]))
		{
			split = key_val_split(cmd->args[i]);
			if (!(is_valid_identifier(split[0])))
				error = perror_env(cmd->args[i]);
			else if (!(change_value_var(split[0], split[1], &(shell->env))))
				append_var(new_var(split[0], split[1]), &(shell->env));
			ft_free_words(split);
		}
		else if (!(is_valid_identifier(cmd->args[i])))
			error = perror_env(cmd->args[i]);
		i++;
	}
	return (error);
}

int		builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
			delete_var(cmd->args[i], &(shell->env));
		else
			error = perror_env(cmd->args[i]);
		i++;
	}
	return (error);
}
