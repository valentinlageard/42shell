/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 16:34:30 by vlageard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_varcalls(char **args, t_shell *shell)
{
	int		i;
	char	*val;
	char	*new_str;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			if ((val = get_envval(&(args[i][1]), shell->env)))
			{
				if (!(new_str = ft_strdup(val)))
					return (-1);
			}
			else
			{
				if (!(new_str = ft_strdup("")))
					return (-1);
			}
			free(args[i]);
			args[i] = new_str;
		}
		i++;
	}
}

t_cmd	*parse_cmd(char *sc_split, t_shell *shell)
{
	t_cmd	*cmd;
	char	**args;

	cmd = new_cmd();
	// Split by whitespaces
	if (!(args = ft_split(sc_split, " \t\n\v\f\r")))
		return (NULL);
	replace_varcalls(args, shell);
	if (is_builtin(args[0]))
	{
		cmd->cmd = ft_strdup(args[0]);
		cmd->is_builtin = 1;
	}
	else
		cmd->cmd = select_binpath(args[0], shell);
	cmd->args = args;
	// TODO : manage other flags (pipe, redirection, etc...)
	return (cmd);
}

t_cmd	**parse(char *line, t_shell *shell)
{
	char	**sc_splits;
	t_cmd	**cmds;
	int		i;

	i = 0;
	// Split by ";"
	if (!(sc_splits = ft_split(line, ";")))
		return (NULL);
	// Create a list of structs
	if (!(cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (ft_wlen(sc_splits) + 1))))
	{
		// TODO : Manage error
		return (NULL);
	}
	cmds[ft_wlen(sc_splits)] = NULL;
	while (sc_splits[i])
	{
		cmds[i] = parse_cmd(sc_splits[i], shell); // TODO : Manage errors
		i++;
	}
	free(sc_splits);
	return (cmds);
}
