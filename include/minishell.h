/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:09 by valentin          #+#    #+#             */
/*   Updated: 2020/11/30 17:16:34 by valentin         ###   ########.fr       */
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

t_shell	*init_shell(char **envp);
void	repl(t_shell *shell);
void	exec_cmd(char **cmd);
char	*select_binpath(char *cmd, t_shell *shell);

// Environ utils
char	*get_envval(char *key, t_shell *shell);

#endif
