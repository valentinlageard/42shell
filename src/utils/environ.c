/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:45:20 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 14:41:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns NULL if the key wasn't found in the environment
// Returns a pointer to the character after '=' if the key was found in the environment

int		envlen(t_var *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**envtowenv(t_var *env)
{
	int		i;
	char	**wenv;
	char	*wvar;

	if (!(wenv = (char **)malloc(sizeof(char *) * (envlen(env) + 1))))
		return (NULL);
	wenv[envlen(env)] = NULL;
	i = 0;
	while (env)
	{
		if (!(wvar = (char *)malloc(sizeof(char) *
		(ft_strlen(env->key) + ft_strlen(env->value) + 2))))
		{
			ft_free_words(wenv);
			return (NULL);
		}
		ft_strlcpy(wvar, env->key, ft_strlen(env->key));
		wvar[ft_strlen(env->key)] = '=';
		ft_strlcpy(&(wvar[ft_strlen(env->key) + 1]), env->value,
			ft_strlen(env->value)); // +1 to add a 0 char ?
		wenv[i] = wvar;
		env = env->next;
	}
	return (wenv);
}

t_env	*wenvtoenv(char **wenv)
{
	
}

char	*get_envval(char *key, t_var *env)
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

void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i++;
	}
}
