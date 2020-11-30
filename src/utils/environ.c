/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:45:20 by valentin          #+#    #+#             */
/*   Updated: 2020/11/30 15:58:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns NULL if the key wasn't found in the environment
// Returns a pointer to the character after '=' if the key was found in the environment

char	*get_envval(char *key, t_shell *shell)
{
	int		i;
	int		key_len;
	char	*val;

	i = 0;
	key_len = ft_strlen(key);
	while (shell->env[i])
	{
		if (ft_strncmp(key, shell->env[i], key_len) == 0
			&& shell->env[i][key_len] == '=')
		{
			val = &(shell->env[i][key_len + 1]);
			return (val);
		}
		i++;
	}
	return (NULL);
}
