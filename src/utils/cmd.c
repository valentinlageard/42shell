/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:20:19 by valentin          #+#    #+#             */
/*   Updated: 2021/01/18 14:30:32 by valentin         ###   ########.fr       */
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
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->main);
	ft_free_words(cmd->args);
	free(cmd);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
	cmds = NULL;
}

t_cmd	**appendrealloc_cmd(t_cmd *cmd, t_cmd **cmds)
{
	int		i;
	int		len_cmds;
	t_cmd	**ncmds;

	i = 0;
	len_cmds = 0;
	if (cmds)
	{
		while (cmds[len_cmds])
			len_cmds++;
	}
	if (!(ncmds = (t_cmd **)malloc(sizeof(t_cmd *) * (len_cmds + 2))))
		return (NULL);
	while (i < len_cmds)
	{
		ncmds[i] = cmds[i];
		i++;
	}
	ncmds[i] = cmd;
	ncmds[i + 1] = NULL;
	free(cmds);
	return (ncmds);
}

int		appendrealloc_arg(char *arg, t_cmd *cmd)
{
	int		i;
	int		len_args;
	char	**args;
	char	**nargs;

	i = 0;
	len_args = 0;
	args = cmd->args;
	while (args[len_args])
		len_args++;
	if (!(nargs = (char **)malloc(sizeof(char *) * (len_args + 2))))
		return (-1);
	while (i < len_args)
	{
		nargs[i] = args[i];
		i++;
	}
	nargs[i] = ft_strdup(arg);
	nargs[i + 1] = NULL;
	free(args);
	cmd->args = nargs;
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_printf("\tCMD : %s\n", cmd->main);
	ft_printf("\tARGS :\n");
	while ((cmd->args)[i])
	{
		ft_printf("\t- args[%d] : %s\n", i, (cmd->args)[i]);
		i++;
	}
	ft_printf("\tIS_VALID : %d\n", cmd->is_valid);
	ft_printf("\tIS_BUILTIN : %d\n", cmd->is_builtin);
}

void	print_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		ft_printf("-> cmds[%d] :\n", i);
		print_cmd(cmds[i]);
		i++;
	}
}
