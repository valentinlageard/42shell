/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2020/12/08 16:24:00 by valentin         ###   ########.fr       */
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

typedef struct	s_var {
	char			*key;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_cmd {
	char	*main;
	char	**args;
	int		is_valid;
	int		is_builtin;
	// TODO : add flags for redirections and pipes.
}				t_cmd;

typedef struct	s_shell {
	t_cmd	**cmds;
	t_var	*env;
}				t_shell;

t_shell	*init_shell(char **envp);
void	repl(t_shell *shell);
t_cmd	**parse(char *line, t_shell *shell);
void	exec(t_shell *shell);
char	*select_binpath(char *cmd, t_shell *shell);

// Cmd utils
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd **cmds);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd **cmds);

// Builtins
int		is_builtin(char *cmd_str);
void	builtin_env(t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);
void	builtin_pwd(t_shell *shell);
void	builtin_echo(t_cmd *cmd);
void	builtin_exit(t_shell *shell);

// Var utils
t_var	*new_var(char *key, char *value);
void	free_var(t_var *var);
void	addlast_var(t_var *var, t_var **env);
int		change_value_var(char *key, char *new_value, t_var **env);
void	delete_var(char *key, t_var **env);

// Environ utils
t_var	*wenvtoenv(char **wenv);
char	**envtowenv(t_var *env);
char	**key_val_split(char *var_str);
void	free_env(t_var *env);
char	*get_envval(char *key, t_var *env);
void	print_env(t_var *env);

// Errors and exit
void	shell_exit(int status, t_shell *shell);

#endif
