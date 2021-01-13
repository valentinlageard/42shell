/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:19:17 by valentin          #+#    #+#             */
/*   Updated: 2021/01/13 01:14:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_slice_and_append(char *line, int start, int i, int type,
	t_tok **ltok)
{
	char	*tok_str;

	tok_str = ft_strslice(line, start, i);
	addlast_tok(new_tok(tok_str, type), ltok);
	free(tok_str);
}

t_tok *tokenize_quotes(char *line)
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
		// Si un quote est rencontré et correspond au quote state
		if ((line[i] == '\'' && quote == 1) || (line[i] == '\"' && quote == 2))
		{
			// On crée un nouveau token et on l'ajoute à la liste
			tok_slice_and_append(line, start, i, quote, &ltok);
			quote = 0;
			start = i + 1;
		}
		// Quote rencontré et le quote state n'est pas enclenché
		else if (!quote && (line[i] == '\"' || line[i] == '\''))
		{
			// On crée un text token
			if (i != 0)
				tok_slice_and_append(line, start, i, 0, &ltok);
			if (line[i] == '\'')
				quote = 1;
			if (line[i] == '\"')
				quote = 2;
			start = i + 1;
		}
		i++;
	}
	// Si on arrive à la fin avec le quote state enclenché -> erreur
	if (quote == 0 && (size_t)start < ft_strlen(line))
		tok_slice_and_append(line, start, i, 0, &ltok);
	if (quote != 0)
	{
		free_ltok(ltok);
		return (NULL);
	}
	return (ltok);
}
