/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 18:19:27 by valentin         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

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

typedef struct	s_var {
	char			*key;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_tok {
	char			*str;
	t_tok_type		type;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_cltok {
	t_tok			*ltok;
	struct s_cltok	*next;
}				t_cltok;

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
}				t_cmdg;

typedef struct	s_pstate {
	t_tok			*tmp;
	t_cmd			*curcmd;
	t_cmdg			*curcmdg;
}				t_pstate;

typedef struct	s_fds {
	int				parent_in;
	int				parent_out;
	int				first;
	int				last;
	int				cur_in;
	int				cur_out;
	int				cur_pipe[2];
}				t_fds;

typedef struct	s_lpid {
	pid_t			pid;
	struct s_lpid	*next;
}				t_lpid;

typedef struct	s_shell {
	t_cltok			*cltoks;
	t_cmdg			*cmdg;
	t_lpid			*lpids;
	t_var			*env;
	int				pass;
	u_char			exit_code;
}				t_shell;

t_shell	*g_shell;

t_shell	*init_shell(char **envp);
void	setup_signal_handling(void);
char	*select_binpath(char *cmd, t_shell *shell);
int		mng_read_err(int read_err, char **line);
int		read_line(int fd, char **line_ptr);
void	prompt(void);

// Parsing
t_cltok	*parse_cltoks(char *line);
t_cmdg	*parse_cmdg(t_tok *ltok, t_shell *shell);
t_tok	*tokenize_quotes(char *line);
t_tok	*tokenize_separators(t_tok *ltok, char *sep_str, t_tok_type sep_type);
void	expand_vars(t_tok *ltok, t_shell *shell);
t_tok	*tokenize_spaces(t_tok *ltok);
t_tok	*tokenize_redirections(t_tok *ltok);
t_cmd	*tok_to_cmds(t_tok *ltok, t_shell *shell);
t_cmd	*new_main_cmd(t_tok *tok, t_shell *shell);
void	update_cmdg(t_pstate *ps);
int		handle_text(t_pstate *ps, t_shell *shell);
int		handle_pipe(t_pstate *ps);
int		handle_input_redirection(t_pstate *ps);
int		handle_output_redirection(t_pstate *ps);
t_cmd	*new_main_cmd(t_tok *tok, t_shell *shell);
t_cmdg	*tok_to_cmdg(t_tok *ltok, t_shell *shell);

// Execution
void	exec(t_shell *shell);
void	exec_cmd(t_cmd *cmd, t_shell *shell);
int		exec_builtin(t_cmd *cmd, t_shell *shell);
int		is_prev_cmd_builtin(t_cmd *cmd, t_cmd *cmds);
int		cmdg_has_unique_builtin(t_cmdg *cmdg);
void	perror_command_not_found(t_cmd *cmd);
void	init_fds(t_fds *fds);
void	store_parent_inout(t_fds *fds);
void	restore_parent_inout(t_fds *fds);
void	set_pipe(t_fds *fds);
void	restore_cur_in(int fd, t_fds *fds);
void	restore_cur_out(int fd, t_fds *fds);
int		select_first(t_cmdg *cmdg, t_fds *fds);
int		select_last(t_cmdg *cmdg, t_fds *fds);
void	update_inout(t_cmd *cmd, t_fds *fds);
void	error_close_fds(t_fds *fds);

// lpids
t_lpid	*new_lpid(pid_t pid);
void	free_lpids(t_lpid *lpids);
int		append_lpid(t_lpid *lpid, t_lpid **lpids);
pid_t	get_last_pid(t_lpid *lpids);
t_cmd	*get_corresponding_cmd(pid_t pid, t_lpid *lpids, t_cmd *cmds);

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
void	print_cmdg(t_cmdg *cmdg);

// Builtins
int		is_builtin(char *cmd_str);
int		builtin_env(t_shell *shell);
int		builtin_export(t_cmd *cmd, t_shell *shell);
int		builtin_unset(t_cmd *cmd, t_shell *shell);
int		builtin_pwd(void);
int		builtin_echo(t_cmd *cmd);
int		builtin_exit(t_cmd *cmd, t_shell *shell);
int		builtin_cd(t_cmd *cmd, t_shell *shell);

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

// Command group tokens
t_cltok	*new_cltok(t_tok *ltok);
void	free_cltok(t_cltok *cltok);
void	free_cltoks(t_cltok *cltoks);
void	shallow_free_cloks(t_cltok *cltoks);
int		append_cltok(t_cltok *cltok, t_cltok **cltoks);

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
void	exit_shell(u_char status, t_shell *shell);
void	pcustom_error(char *str_error);
void	perrno(void);
void	pcustom_error_exit(char *str_error, t_shell *shell);
void	perrno_exit(t_shell *shell);

#endif
