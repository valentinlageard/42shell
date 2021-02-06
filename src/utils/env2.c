/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:39:22 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 15:43:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_var *env)
{
	t_var	*tmp;
	t_var	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		free_var(tmp);
		tmp = next;
	}
	env = NULL;
}

void	print_env(t_var *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
