/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:44:06 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 21:03:20 by vlageard         ###   ########.fr       */
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

	slash_cmd = ft_strjoin("/", cmd); // TODO : Check errors
	path_val = get_envval("PATH", shell->env); // TODO : Check errors
	bpaths = ft_split(path_val, ":"); // TODO : Check errors
	i = 0;
	while (bpaths[i])
	{
		bpath = ft_strjoin(bpaths[i], slash_cmd);
		if (file_exists(bpath))
		{
			free(slash_cmd);
			free(path_val);
			ft_free_words(bpaths);
			return (bpath);
		}
		free(bpath);
		i++;
	}
	free(slash_cmd);
	free(path_val);
	return (NULL);
}

char	*select_binpath(char *cmd, t_shell *shell)
{
	if (file_exists(cmd))
		return (cmd);
	else
		return (get_binpath(cmd, shell));
}
