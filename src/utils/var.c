/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:12:07 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 15:36:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*new_var(char *key, char *value)
{
	t_var	*var;

	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	if (!(var->key = ft_strdup(key)))
	{
		free(var);
		return (NULL);
	}
	if (!(var->value = ft_strdup(value)))
	{
		free(var->key);
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}

void	free_var(t_var *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

void	append_var(t_var *var, t_var **env)
{
	t_var	*tmp;

	if (!(*env))
		*env = var;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = var;
	}
}

int		change_value_var(char *key, char *new_value, t_var **env)
{
	t_var	*tmp;
	int		key_len;

	tmp = *env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, key_len) == 0)
		{
			free(tmp->value);
			if (!(tmp->value = ft_strdup(new_value)))
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	delete_var(char *key, t_var **env)
{
	t_var	*prev;
	t_var	*tmp;
	int		key_len;

	prev = NULL;
	tmp = *env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, key_len) == 0)
		{
			if (!prev)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free_var(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
