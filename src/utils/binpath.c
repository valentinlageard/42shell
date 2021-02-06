/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:44:06 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 15:53:13 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		file_exists(char *path)
{
	struct stat	buf;

	return (stat(path, &buf) == 0);
}

char	*get_binpath(char *cmd, t_shell *shell)
{
	char	*slash_cmd;
	char	*path_val;
	char	**bpaths;
	char	*bpath;
	int		i;

	slash_cmd = ft_strjoin("/", cmd); // TODO : Check for ENOMEM
	path_val = get_envval("PATH", shell->env);
	bpaths = ft_split(path_val, ":"); // TODO : Check for ENOMEM
	i = 0;
	while (bpaths[i])
	{
		bpath = ft_strjoin(bpaths[i], slash_cmd);
		if (file_exists(bpath))
		{
			free(slash_cmd);
			ft_free_words(bpaths);
			return (bpath);
		}
		free(bpath);
		bpath = NULL;
		i++;
	}
	ft_free_words(bpaths);
	free(slash_cmd);
	return (NULL);
}

char	*select_binpath(char *cmd, t_shell *shell)
{
	if (cmd[0] && cmd[0] == '/' && file_exists(cmd))
		return (ft_strdup(cmd));
	else
		return (get_binpath(cmd, shell));
}
