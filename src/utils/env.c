/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:50:17 by valentin          #+#    #+#             */
/*   Updated: 2021/02/09 18:01:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_strlcpy(wvar, env->key, ft_strlen(env->key) + 1);
		wvar[ft_strlen(env->key)] = '=';
		ft_strlcpy(&(wvar[ft_strlen(env->key) + 1]), env->value,
			ft_strlen(env->value) + 1);
		wenv[i] = wvar;
		i++;
		env = env->next;
	}
	return (wenv);
}

char	**key_val_split(char *var_str)
{
	char	**key_val;
	int		i;

	if (!(key_val = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (!(key_val[0] = (char *)malloc(sizeof(char) * (i + 1))))
	{
		free(key_val);
		return (NULL);
	}
	ft_strlcpy(key_val[0], var_str, i + 1);
	if (!(key_val[1] = ft_strdup(&(var_str[i + 1]))))
	{
		free(key_val);
		return (NULL);
	}
	key_val[2] = NULL;
	return (key_val);
}

t_var	*wenvtoenv(char **wenv)
{
	int		i;
	t_var	*env;
	t_var	*var;
	char	**split;

	i = 0;
	env = NULL;
	while (wenv[i])
	{
		if (!(split = key_val_split(wenv[i])))
		{
			pcustom_error("minishell: env conversion error\n");
			continue ;
		}
		var = new_var(split[0], split[1]);
		ft_free_words(split);
		append_var(var, &env);
		i++;
	}
	return (env);
}

char	*get_envval(char *key, t_var *env)
{
	size_t		k_len;

	if (!key)
		return (NULL);
	k_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(key, env->key, k_len) == 0 &&
			ft_strlen(env->key) == k_len)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
