/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:45:20 by valentin          #+#    #+#             */
/*   Updated: 2020/12/05 16:48:08 by vlageard         ###   ########.fr       */
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
			ft_strlen(env->value));
		wenv[i] = wvar;
		env = env->next;
	}
	return (wenv);
}

t_var	*wenvtoenv(char **wenv)
{
	int		i;
	t_var	*env;
	t_var	*var;
	char	**equal_split;

	i = 0;
	env = NULL;
	while (wenv[i])
	{
		equal_split = ft_split(wenv[i], "="); // TODO : check for errors !
		// TODO : ONLY THE FIRST EQUAL IS USED FOR SPLITTING !
		var = new_var(equal_split[0], equal_split[1]);
		ft_free_words(equal_split);
		addlast_var(var, &env);
		i++;
	}
	return (env);
}

char	*get_envval(char *key, t_var *env)
{
	int		key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, key_len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	print_env(t_var *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
