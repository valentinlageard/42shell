/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:47:54 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 16:40:51 by valentin         ###   ########.fr       */
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
			append_tok(new_tok(words[i], txt), nltok);
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
		if (tmp->type == txt)
			split_by_spaces(tmp, &nltok);
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}

int		append_next_as_redirection(t_tok *tmp, t_tok **nltok)
{
	t_tok	*next;

	next = tmp->next;
	if (next)
	{
		if (tok_is_identifier(next))
		{
			append_tok(new_tok(next->str, tmp->type), nltok);
			return (0);
		}
	}
	return (-1);
}

t_tok	*tokenize_redirections(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		if (tmp->type == inr || tmp->type == outr || tmp->type == outrapp)
		{
			if (append_next_as_redirection(tmp, &nltok) < 0)
			{
				pcustom_error("minishell: redirection syntax error\n");
				free_ltok(ltok);
				if (nltok)
					free_ltok(nltok);
				return (NULL);
			}
			tmp = tmp->next;
		}
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}
