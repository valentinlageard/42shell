/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:26:03 by valentin          #+#    #+#             */
/*   Updated: 2021/02/08 17:10:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_by_spaces(t_tok *tok, t_tok **nltok)
{
	t_tok	*ntok;
	int		i;
	char	**words;
	int		lch_idx;
	int		lw_idx;

	i = 0;
	words = ft_split(tok->str, " \t\v\f\r");
	lch_idx = ft_strlen(tok->str) - 1;
	lw_idx = ft_wlen(words) - 1;
	if (words)
	{
		while (words[i])
		{
			ntok = new_tok(words[i], txt);
			if (i == 0 && !ft_iscinstr(tok->str[0], " \t\v\f\r"))
				ntok->is_fchar_sp = 0;
			if (i == lw_idx && !ft_iscinstr(tok->str[lch_idx], " \t\v\f\r"))
				ntok->is_lchar_sp = 0;
			append_tok(ntok, nltok);
			i++;
		}
		ft_free_words(words);
	}
}

t_tok	*tokenize_spaces(t_tok *ltok)
{
	t_tok	*ntok;
	t_tok	*tmp;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		if (tmp->type == txt)
			split_by_spaces(tmp, &nltok);
		else if (tmp->type == squo || tmp->type == dquo)
		{
			ntok = new_tok(tmp->str, tmp->type);
			if (tmp->next &&
				(tmp->next->type == squo || tmp->next->type == dquo))
				ntok->next_was_quote = 1;
			append_tok(ntok, &nltok);
		}
		else
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		tmp = tmp->next;
	}
	free_ltok(&ltok);
	return (nltok);
}

int		should_concatenate(t_tok *prev, t_tok *next)
{
	if (!next)
		return (0);
	if (prev->type == squo || prev->type == dquo)
	{
		if (prev->next_was_quote)
			return (1);
		else if (!(next->is_fchar_sp) && next->type == txt)
			return (1);
	}
	if (prev->type == txt && !prev->is_lchar_sp)
	{
		if (next->type == squo || next->type == dquo)
			return (1);
	}
	return (0);
}

t_tok	*concatenate_tokens(t_tok *prev_tok, t_tok *next_tok, int free_prev)
{
	t_tok	*ntok;
	char	*ntok_str;

	ntok = NULL;
	ntok_str = ft_strjoin(prev_tok->str, next_tok->str);
	if (free_prev)
		free_tok(&prev_tok);
	if (ntok_str)
	{
		ntok = new_tok(ntok_str, txt);
		free(ntok_str);
		return (ntok);
	}
	return (NULL);
}

t_tok	*concatenate_identifiers(t_tok *ltok)
{
	t_tok	*tmp;
	t_tok	*ntok;
	t_tok	*nltok;

	tmp = ltok;
	nltok = NULL;
	while (tmp)
	{
		ntok = NULL;
		while (tok_is_identifier(tmp) && should_concatenate(tmp, tmp->next))
		{
			if (!ntok)
				ntok = concatenate_tokens(tmp, tmp->next, 0);
			else
				ntok = concatenate_tokens(ntok, tmp->next, 1);
			tmp = tmp->next;
		}
		if (!ntok)
			append_tok(new_tok(tmp->str, tmp->type), &nltok);
		else
			append_tok(ntok, &nltok);
		tmp = tmp->next;
	}
	free_ltok(&ltok);
	return (nltok);
}
