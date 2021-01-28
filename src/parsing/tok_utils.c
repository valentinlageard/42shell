/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:46:55 by valentin          #+#    #+#             */
/*   Updated: 2021/01/28 14:46:57 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slice_append_tok(char *line, int start, int i, int type,
	t_tok **ltok)
{
	char	*tok_str;

	tok_str = ft_strslice(line, start, i);
	append_tok(new_tok(tok_str, type), ltok);
	free(tok_str);
}

t_tok	*tokenize_quotes(char *line)
{
	int		i;
	int		start;
	int		quote;
	t_tok	*ltok;

	i = 0;
	start = 0;
	quote = 0; // 0 no quote, 1 single quote, 2 double quote
	ltok = NULL;
	while (line[i])
	{
		if ((line[i] == '\'' && quote == 1) || (line[i] == '\"' && quote == 2))
		{
			slice_append_tok(line, start, i, quote, &ltok);
			quote = 0;
			start = i + 1;
		}
		else if (!quote && (line[i] == '\"' || line[i] == '\''))
		{
			if (start != i)
				slice_append_tok(line, start, i, 0, &ltok);
			if (line[i] == '\'')
				quote = 1;
			if (line[i] == '\"')
				quote = 2;
			start = i + 1;
		}
		i++;
	}
	if (quote == 0 && (size_t)start < ft_strlen(line))
		slice_append_tok(line, start, i, 0, &ltok);
	if (quote != 0)
	{
		free_ltok(ltok);
		return (NULL);
	}
	return (ltok);
}

t_tok	*separate_token(t_tok *tok, char *sep_str, int sep_type)
{
	int		i;
	int		start;
	t_tok	*ntok;

	i = 0;
	start = 0;
	ntok = NULL;
	while (tok->str[i])
	{
		if (ft_strncmp(sep_str, &(tok->str[i]), ft_strlen(sep_str)) == 0)
		{
			if (start != i)
				slice_append_tok(tok->str, start, i, 0, &ntok);
			append_tok(new_tok(sep_str, sep_type), &ntok);
			start = i + ft_strlen(sep_str);
		}
		i++;
	}
	if (start != i)
		slice_append_tok(tok->str, start, i, 0, &ntok);
	return (ntok);
}

t_tok	*tokenize_separators(t_tok *ltok, char *sep_str, int sep_type)
{
	t_tok	*tmp;
	t_tok	*ntok;
	t_tok	*nltok;

	ntok = NULL;
	nltok = NULL;
	tmp = ltok;
	while (tmp)
	{
		if (tmp->type == 0) // Check special characters allowed in ""
			ntok = separate_token(tmp, sep_str, sep_type);
		else
			ntok = new_tok(tmp->str, tmp->type);
		append_tok(ntok, &nltok);
		tmp = tmp->next;
	}
	free_ltok(ltok);
	return (nltok);
}
