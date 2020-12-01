/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2020/12/01 16:14:59 by valentin         ###   ########.fr       */
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
	//int		is_piped;
}				t_cmd;

t_shell	*init_shell(char **envp);
void	repl(t_shell *shell);
t_cmd	**parse(char *line, t_shell *shell);
void	exec(t_cmd **cmds, t_shell *shell);
char	*select_binpath(char *cmd, t_shell *shell);

// Cmd utils
t_cmd	*new_cmd(void);
void	free_cmd(t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd **cmds);

// Environ utils
char	*get_envval(char *key, t_shell *shell);

#endif
