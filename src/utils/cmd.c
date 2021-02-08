/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:20:19 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 19:00:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->main = NULL;
	cmd->args = NULL;
	cmd->is_valid = 1;
	cmd->is_builtin = 0;
	cmd->is_main_path = 0;
	cmd->next = NULL;
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->main);
	ft_free_words(cmd->args);
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_cmd(cmds);
		cmds = next;
	}
}

void	append_cmd(t_cmd *cmd, t_cmd **cmds)
{
	t_cmd	*tmp;

	if (!(*cmds))
		*cmds = cmd;
	else
	{
		tmp = *cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
}

int		appendrealloc_arg(char *arg, t_cmd *cmd)
{
	int		i;
	int		len_args;
	char	**nargs;

	i = 0;
	len_args = 0;
	while (cmd->args[len_args])
		len_args++;
	if (!(nargs = (char **)malloc(sizeof(char *) * (len_args + 2))))
		return (-1);
	while (i < len_args)
	{
		nargs[i] = cmd->args[i];
		i++;
	}
	if (!(nargs[i] = ft_strdup(arg)))
	{
		free(nargs);
		return (-1);
	}
	nargs[i + 1] = NULL;
	free(cmd->args);
	cmd->args = nargs;
	return (0);
}
