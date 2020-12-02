/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2020/12/02 17:00:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct	s_shell {
	char	**env;
}				t_shell;

typedef struct	s_cmd {
	char	*cmd;
	char	**args;
	int		is_valid;
	int		is_builtin;
	// TODO : add flags for redirections and pipes.
}				t_cmd;

t_shell	*init_shell(char **envp);
void	repl(t_shell *shell);
t_cmd	**parse(char *line, t_shell *shell);
void	exec(t_cmd **cmds, t_shell *shell);
char	*select_binpath(char *cmd, t_shell *shell);

// Cmd utils
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd **cmds);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd **cmds);

// Builtins
int		is_builtin(char *cmd_str);
void	builtin_exit(t_shell *shell);

// Environ utils
char	*get_envval(char *key, t_shell *shell);

// Errors and exit

void	shell_exit(int status, t_shell *shell);

#endif
