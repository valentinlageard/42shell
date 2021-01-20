/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:53:23 by valentin          #+#    #+#             */
/*   Updated: 2021/01/19 14:10:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(t_tok *tok, int *i, t_shell *shell)
{
	int		j;
	char	*slice;
	char	*val;
	int		nstr_size;
	char	*nstr;

	j = *i + 1;
	while ((ft_isalnum(tok->str[j])) || tok->str[j] == '_')
		j++;
	slice = ft_strslice(tok->str, *i + 1, j);
	val = get_envval(slice, shell->env);
	if (!val)
		val = "";
	nstr_size = *i + ft_strlen(val) + (ft_strlen(tok->str) - j) + 1;
	nstr = (char *)malloc(sizeof(char) * nstr_size); // TODO : PROTECT
	ft_memset(nstr, '\0', nstr_size);
	ft_memcpy(nstr, tok->str, *i);
	ft_memcpy(&(nstr[*i]), val, ft_strlen(val));
	ft_memcpy(&(nstr[*i + ft_strlen(val)]), &(tok->str[j]),
		ft_strlen(tok->str) - j);
	free(tok->str);
	tok->str = nstr;
	*i = j;
	free(slice);
}

void	expand_vars(t_tok *ltok, t_shell *shell)
{
	int		i;
	t_tok	*tmp;

	tmp = ltok;
	while (tmp)
	{
		if (tmp->type == 0 || tmp->type == 2)
		{
			i = 0;
			while (tmp->str[i])
			{
				if (tmp->str[i] == '$')
					expand_var(tmp, &i, shell);
				i++;
			}
		}
		tmp = tmp->next;
	}
}
