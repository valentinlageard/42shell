/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:47:54 by valentin          #+#    #+#             */
/*   Updated: 2021/01/28 14:51:00 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_by_spaces(t_tok *tok, t_tok **nltok)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(tok->str, " \t\n");
	if (words)
	{
		while (words[i])
		{
			append_tok(new_tok(words[i], 0), nltok);
			i++;
		}
		ft_free_words(words);
	}
}

t_tok	*tokenize_spaces(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		if (tmp->type == 0)
			split_by_spaces(tmp, &nltok);
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}

void	append_next_as_redirection(t_tok *tmp, t_tok *nltok)
{
	t_tok	*next;

	next = tmp->next;
	if (next)
	{
		if (next->type == 0 || next->type == 1 || next->type == 2)
			append_tok(new_tok(next->str, tmp->type), &nltok);
		// TODO : else parse error
	}
	// TODO : else parse error !
}

t_tok	*tokenize_redirections(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		if (tmp->type == 5 || tmp->type == 6 || tmp->type == 7)
		{
			append_next_as_redirection(tmp, nltok);
			tmp = tmp->next;
		}
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}
