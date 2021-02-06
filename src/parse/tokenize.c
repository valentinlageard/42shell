/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:46:55 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 19:59:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*manage_tokenize_quote_error(t_tok **ltok, int quote)
{
	free_ltok(ltok);
	if (quote == 1)
		pcustom_error("minishell: syntax error near unexpected token `''\n");
	if (quote == 2)
		pcustom_error("minishell: syntax error near unexpected token `\"'\n");
	return (NULL);
}

void	manage_quote_state(char *line, t_si *si, int *quote, t_tok **ltok)
{
	if ((line[si->end] == '\'' && *quote == 1) ||
		(line[si->end] == '\"' && *quote == 2))
	{
		slice_append_tok(line, si, *quote, ltok);
		*quote = 0;
		si->start = si->end + 1;
	}
	else if (!*quote && (line[si->end] == '\"' || line[si->end] == '\''))
	{
		if (si->start != si->end)
			slice_append_tok(line, si, 0, ltok);
		if (line[si->end] == '\'')
			*quote = 1;
		if (line[si->end] == '\"')
			*quote = 2;
		si->start = si->end + 1;
	}
}

t_tok	*tokenize_quotes(char *line)
{
	t_si	si;
	int		quote;
	t_tok	*ltok;

	si.start = 0;
	si.end = 0;
	quote = 0;
	ltok = NULL;
	while (line[si.end])
	{
		manage_quote_state(line, &si, &quote, &ltok);
		si.end++;
	}
	if (quote == 0 && (size_t)si.start < ft_strlen(line))
		slice_append_tok(line, &si, txt, &ltok);
	if (quote != 0)
		return (manage_tokenize_quote_error(&ltok, quote));
	return (ltok);
}

t_tok	*separate_token(t_tok *tok, char *sep_str, t_tok_type sep_type)
{
	t_si	si;
	t_tok	*ntok;

	si.start = 0;
	si.end = 0;
	ntok = NULL;
	while (tok->str[si.end])
	{
		if (ft_strncmp(sep_str, &(tok->str[si.end]), ft_strlen(sep_str)) == 0)
		{
			if (si.start != si.end)
				slice_append_tok(tok->str, &si, 0, &ntok);
			append_tok(new_tok(sep_str, sep_type), &ntok);
			si.start = si.end + ft_strlen(sep_str);
		}
		si.end++;
	}
	if (si.start != si.end)
		slice_append_tok(tok->str, &si, 0, &ntok);
	return (ntok);
}

t_tok	*tokenize_separators(t_tok *ltok, char *sep_str, t_tok_type sep_type)
{
	t_tok	*tmp;
	t_tok	*ntok;
	t_tok	*nltok;

	ntok = NULL;
	nltok = NULL;
	tmp = ltok;
	while (tmp)
	{
		if (tmp->type == txt)
			ntok = separate_token(tmp, sep_str, sep_type);
		else
			ntok = new_tok(tmp->str, tmp->type);
		append_tok(ntok, &nltok);
		tmp = tmp->next;
	}
	free_ltok(&ltok);
	return (nltok);
}
