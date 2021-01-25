/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:22:40 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 18:21:16 by valentin         ###   ########.fr       */
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

t_tok	*tokenize_input_redirections(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*next;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		if (tmp->type == 5)
		{
			next = tmp->next;
			if (next)
			{
				if (next->type == 0 || next->type == 1 || next->type == 2)
				{
					append_tok(new_tok(next->str, 5), &nltok);
					tmp = next;
				}
				// else parse error
			// else parse error !
			}
		}
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}
