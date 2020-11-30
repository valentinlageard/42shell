/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:44:06 by valentin          #+#    #+#             */
/*   Updated: 2020/11/30 17:29:17 by valentin         ###   ########.fr       */
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
	path_val = get_envval("PATH", shell); // TODO : Check errors
	bpaths = ft_split(path_val, ":"); // TODO : Check errors
	i = 0;
	while (bpaths[i])
	{
		bpath = ft_strjoin(bpaths[i], slash_cmd);
		ft_printf("bpath : %s\n", bpath);
		if (file_exists(bpath))
		{
			ft_printf("%s exists !\n", bpath);
			free(slash_cmd);
			return (bpath);
		}
		free(bpath);
		i++;
	}
	free(slash_cmd);
	return (NULL);
}

char	*select_binpath(char *cmd, t_shell *shell)
{
	if (file_exists(cmd))
		return (cmd);
	else
		return (get_binpath(cmd, shell));
}
