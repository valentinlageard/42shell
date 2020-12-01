/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:15:55 by valentin          #+#    #+#             */
/*   Updated: 2020/12/01 16:31:21 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	**parse(char *line, t_shell *shell)
{
	char	**semicol_split;
	char	**args;
	t_cmd	*cmd;
	t_cmd	**cmds;
	int		i;

	i = 0;
	// Split by ";"
	if (!(semicol_split = ft_split(line, ";")))
		return (NULL);
	// Create a list of structs
	if (!(cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (ft_wlen(semicol_split) + 1))))
	{
		// TODO : Deallocate semicol_split
		return (NULL);
	}
	cmds[ft_wlen(semicol_split)] = NULL;
	while (semicol_split[i])
	{
		// Split by whitespaces
		if (!(args = ft_split(semicol_split[i], " \t\n\v\f\r")))
		{
			// TODO : Deallocate semicol_split, cmds and previously allocated cmd
			return (NULL);
		}
		cmd = new_cmd();
		// TODO : If builtin, set is_builtin to 1
		cmd->cmd = select_binpath(args[0], shell);
		cmd->args = args;
		// TODO : parse arguments. ex : cmd->parameters = parse_args(args);
		// Should replace call to variables and allocate everything relevant.
		// TODO : manage flags (pipe, redirection, etc...)
		cmds[i] = cmd;
		i++;
	}
	free(semicol_split);
	return (cmds);
}
