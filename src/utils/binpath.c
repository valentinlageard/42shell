/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:44:06 by valentin          #+#    #+#             */
/*   Updated: 2021/02/09 18:11:41 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		file_exists(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			pcustom_error("minishell: ");
			pcustom_error(path);
			pcustom_error(": Is a directory\n");
			return (2);
		}
		return (1);
	}
	else
		return (0);
}

char	*get_binpath(char *cmd, t_shell *shell)
{
	char	*slash_cmd;
	char	*path_val;
	char	**bpaths;
	char	*bpath;
	int		i;

	bpath = NULL;
	if (!(path_val = get_envval("PATH", shell->env)) ||
		!(slash_cmd = ft_strjoin("/", cmd)))
		return (NULL);
	if ((bpaths = ft_split(path_val, ":")))
	{
		i = -1;
		while (bpaths[++i])
		{
			bpath = ft_strjoin(bpaths[i], slash_cmd);
			if (file_exists(bpath))
				break ;
			free(bpath);
			bpath = NULL;
		}
		ft_free_words(bpaths);
	}
	free(slash_cmd);
	return (bpath);
}

void	select_binpath(t_cmd **ncmd, char *cmd_str, t_shell *shell)
{
	int	file_type;

	if (ft_strlen(cmd_str) == 0)
		return ;
	else if (cmd_str[0] == '/' || cmd_str[0] == '.')
	{
		(*ncmd)->is_main_path = 1;
		file_type = file_exists(cmd_str);
		if (file_type == 1)
			(*ncmd)->main = ft_strdup(cmd_str);
		else if (file_type == 0)
		{
			pcustom_error("minishell: ");
			pcustom_error(cmd_str);
			pcustom_error(": ");
			perrno();
			pcustom_error("\n");
		}
	}
	else
		(*ncmd)->main = get_binpath(cmd_str, shell);
}
