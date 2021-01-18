/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:22:40 by valentin          #+#    #+#             */
/*   Updated: 2021/01/16 14:43:45 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_by_spaces(t_tok *tok, t_tok **nltok)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(tok->str, " \t\n\v\f\r");
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
