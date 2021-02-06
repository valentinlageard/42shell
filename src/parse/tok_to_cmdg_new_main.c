/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_cmdg_new_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:18:56 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 18:26:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			fill_builtin_or_binpath(char *arg0, t_cmd **ncmd, t_shell *shell)
{
	if (is_builtin(arg0))
	{
		if (!((*ncmd)->main = ft_strdup(arg0)))
		{
			free_cmd(*ncmd);
			return (-1);
		}
		(*ncmd)->is_builtin = 1;
	}
	else
		(*ncmd)->main = select_binpath(arg0, shell);
	return (0);
}

t_cmd		*new_main_cmd(t_tok *tok, t_shell *shell)
{
	t_cmd	*ncmd;
	char	**args;

	ncmd = new_cmd();
	if (!(args = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(args[0] = ft_strdup(tok->str)))
	{
		free_cmd(ncmd);
		ft_free_words(args);
		return (NULL);
	}
	args[1] = NULL;
	ncmd->args = args;
	if (!ft_strlen(args[0]))
		ncmd->is_valid = 0;
	if ((fill_builtin_or_binpath(args[0], &ncmd, shell) != 0))
		return (NULL);
	if (!ncmd->main)
		ncmd->is_valid = 0;
	return (ncmd);
}
