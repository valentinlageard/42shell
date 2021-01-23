/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:03:58 by valentin          #+#    #+#             */
/*   Updated: 2021/01/23 17:45:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	ft_printf("-> Executing : %s\n", cmd->main);
	if (ft_strncmp(cmd->main, "exit", ft_strlen(cmd->main)) == 0)
		builtin_exit(shell);
	if (ft_strncmp(cmd->main, "env", ft_strlen(cmd->main)) == 0)
		builtin_env(shell);
	if (ft_strncmp(cmd->main, "unset", ft_strlen(cmd->main)) == 0)
		builtin_unset(cmd, shell);
	if (ft_strncmp(cmd->main, "export", ft_strlen(cmd->main)) == 0)
		builtin_export(cmd, shell);
	if (ft_strncmp(cmd->main, "pwd", ft_strlen(cmd->main)) == 0)
		builtin_pwd(shell);
	if (ft_strncmp(cmd->main, "echo", ft_strlen(cmd->main)) == 0)
		builtin_echo(cmd);
	if (ft_strncmp(cmd->main, "cd", ft_strlen(cmd->main)) == 0)
		builtin_cd(cmd, shell);
}

void	exec_simple_builtin(t_cmd *cmd, t_shell *shell)
{
	if (cmd->is_valid)
		exec_builtin(cmd, shell);
}

void	exec_bin(t_cmd *cmd, t_shell *shell)
{
	char	**wenv;

	ft_printf("-> Executing : %s\n", cmd->main);
	wenv = envtowenv(shell->env);
	execve(cmd->main, cmd->args, wenv);
}

void	exec_cmdg(t_cmdg *curcmdg, t_shell *shell)
{
	pid_t	pid;
	int		parent_in;
	int		parent_out;
	int		cur_in;
	int		cur_out;
	int		cur_pipe[2];
	t_cmd	*curcmd;

	parent_in = dup(0);
	parent_out = dup(1);
	curcmd = curcmdg->cmds;
	cur_in = dup(parent_in);
	while (curcmd)
	{
		dup2(cur_in, 0);
		close(cur_in);
		// Si c'est la dernière commande
		if (!(curcmd->next))
		{
			// Output la dernière commande dans le stdout du parent.
			cur_out = dup(parent_out);
		}
		// Si ce n'est pas la dernière commande
		else
		{
			// Créer un pipe.
			pipe(cur_pipe);
			cur_in = cur_pipe[0];
			cur_out = cur_pipe[1];
		}
		dup2(cur_out, 1);
		close(cur_out);
		// Forker
		pid = fork();
		// Dans l'enfant
		if (pid == 0)
		{
			if (curcmd->is_valid)
			{
				if (curcmd->is_builtin)
				{
					exec_builtin(curcmd, shell);
					shell_exit(EXIT_SUCCESS, shell);
				}
				else
					exec_bin(curcmd, shell);
			}
		}
		curcmd = curcmd->next;
	}
	dup2(parent_in, 0);
	dup2(parent_out, 1);
	close(parent_in);
	close(parent_out);
	waitpid(pid, NULL, WUNTRACED); // STATUS ?
}

void	exec(t_shell *shell)
{
	t_cmdg	*curcmdg;

	curcmdg = shell->cmdgs;
	while (curcmdg)
	{
		if (!(curcmdg->cmds->next) && (curcmdg->cmds->is_builtin))
		{
			ft_printf("Executing simple builtin\n");
			exec_simple_builtin(curcmdg->cmds, shell);
		}
		else
		{
			ft_printf("Executing command group\n");
			exec_cmdg(curcmdg, shell);
		}
		curcmdg = curcmdg->next;
	}
	free_cmdgs(shell->cmdgs);
}
