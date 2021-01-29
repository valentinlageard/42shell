/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 16:38:28 by valentin         ###   ########.fr       */
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
# include <fcntl.h>
# include "../libft/libft.h"

# define PATH_MAX 4096

typedef struct	s_var {
	char			*key;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef enum	e_tok_type {
	txt,
	squo,
	dquo,
	sep,
	pip,
	inr,
	outr,
	outrapp
}				t_tok_type;

typedef struct	s_tok {
	char			*str;
	t_tok_type		type;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_cmd {
	char			*main;
	char			**args;
	int				is_valid;
	int				is_builtin;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_inr {
	char			*path;
	struct s_inr	*next;
}				t_inr;

typedef struct	s_outr {
	char			*path;
	int				is_append;
	struct s_outr	*next;
}				t_outr;

typedef struct	s_cmdg {
	t_cmd			*cmds;
	t_inr			*in_redirs;
	t_outr			*out_redirs;
	struct s_cmdg	*next;
}				t_cmdg;

typedef struct	s_pstate {
	t_tok	*tmp;
	t_cmd	*curcmd;
	t_cmdg	*curcmdg;
	t_cmdg	*cmdgs;
}				t_pstate;

typedef struct	s_fds {
	int		parent_in;
	int		parent_out;
	int		first;
	int		last;
	int		cur_in;
	int		cur_out;
	int		cur_pipe[2];
}				t_fds;

typedef struct	s_shell {
	t_cmdg	*cmdgs;
	t_var	*env;
}				t_shell;

t_shell	*init_shell(char **envp);
void	repl(t_shell *shell);
char	*select_binpath(char *cmd, t_shell *shell);

// Parsing
t_cmdg	*parse(char *line, t_shell *shell);
t_tok	*tokenize_quotes(char *line);
t_tok	*tokenize_separators(t_tok *ltok, char *sep_str, int sep_type);
void	expand_vars(t_tok *ltok, t_shell *shell);
t_tok	*tokenize_spaces(t_tok *ltok);
t_tok	*tokenize_redirections(t_tok *ltok);
t_cmd	*tok_to_cmds(t_tok *ltok, t_shell *shell);
t_cmdg	*tok_to_cmdgs(t_tok *ltok, t_shell *shell);

// Execution
void	exec(t_shell *shell);
void	exec_cmd(t_cmd *cmd, t_shell *shell);
void	exec_simple_builtin(t_cmd *cmd, t_shell *shell);
t_fds	*new_fds(void);
void	store_parent_inout(t_fds *fds);
void	restore_parent_inout(t_fds *fds);
void	set_pipe(t_fds *fds);
void	restore_cur_in(int fd, t_fds *fds);
void	restore_cur_out(int fd, t_fds *fds);
int		select_first(t_cmdg *cmdg, t_fds *fds);
int		select_last(t_cmdg *cmdg, t_fds *fds);

// Cmd utils
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmd *cmds);
void	append_cmd(t_cmd *cmd, t_cmd **cmds);
int		appendrealloc_arg(char *arg, t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd *cmds);

// Cmdg utils
t_cmdg	*new_cmdg(void);
void	free_cmdg(t_cmdg *cmdg);
void	free_cmdgs(t_cmdg *cmdgs);
void	append_cmdg(t_cmdg *cmdg, t_cmdg **cmdgs);
void	print_cmdg(t_cmdg *cmdg);
void	print_cmdgs(t_cmdg *cmdgs);

// Builtins
int		is_builtin(char *cmd_str);
void	builtin_env(t_shell *shell);
void	builtin_export(t_cmd *cmd, t_shell *shell);
void	builtin_unset(t_cmd *cmd, t_shell *shell);
void	builtin_pwd(t_shell *shell);
void	builtin_echo(t_cmd *cmd);
void	builtin_exit(t_shell *shell);
void	builtin_cd(t_cmd *cmd, t_shell *shell);

// Redirections
t_inr	*new_inr(char *path);
void	append_inr(t_inr *in_redir, t_inr **in_redirs);
void	free_inrs(t_inr *inrs);
void	print_inrs(t_inr *inrs);
t_outr	*new_outr(char *path, int is_append);
void	append_outr(t_outr *out_redir, t_outr **out_redirs);
void	free_outrs(t_outr *outrs);
void	print_outrs(t_outr *outrs);

// Tokens

t_tok	*new_tok(char *str, t_tok_type type);
void	free_tok(t_tok *tok);
int		append_tok(t_tok *tok, t_tok **ltok);
void	free_ltok(t_tok *tok);
int		tok_is_identifier(t_tok *tok);
void	print_tok(t_tok *tok);
void	print_ltok(t_tok *tok);

// Var utils
t_var	*new_var(char *key, char *value);
void	free_var(t_var *var);
void	append_var(t_var *var, t_var **env);
int		change_value_var(char *key, char *new_value, t_var **env);
void	delete_var(char *key, t_var **env);

// Environ utils
t_var	*wenvtoenv(char **wenv);
char	**envtowenv(t_var *env);
char	**key_val_split(char *var_str);
void	free_env(t_var *env);
char	*get_envval(char *key, t_var *env);
void	print_env(t_var *env);

// Dir utils
void	update_pwd(t_shell *shell);

// Errors and exit
void	exit_shell(int status, t_shell *shell);
void	pcustom_error(char *str_error);
void	perrno(void);
void	pcustom_error_exit(char *str_error, t_shell *shell);
void	perrno_exit(t_shell *shell);

#endif
