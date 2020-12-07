/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2020/12/08 00:25:00 by valentin         ###   ########.fr       */
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
			ft_printf("$ encountered : args[%d] : %s\n", i, args[i]);
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
	return (-1);
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
		cmd->main = ft_strdup(args[0]);
		cmd->is_builtin = 1;
	}
	else
		cmd->main = select_binpath(args[0], shell);
	if (!cmd->main)
		cmd->is_valid = 0;
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
	if (!(sc_splits = ft_split(line, ";")))
		return (NULL);
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
	ft_free_words(sc_splits);
	return (cmds);
}
