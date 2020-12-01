/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:05:34 by valentin          #+#    #+#             */
/*   Updated: 2020/12/01 15:15:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envdup(char **envp)
{
	char	**env;
	char	*str;
	int		i;

	i = 0;
	if (!(env = (char **)malloc((ft_wlen(envp) + 1) * sizeof(char *))))
		return (NULL);
	while (envp[i])
	{
		if (!(str = ft_strdup(envp[i])))
		{
			ft_free_words(env);
			return (NULL);
		}
		env[i] = str;
		i++;
	}
	return (env);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	shell->env = envdup(envp);
	return (shell);
}
