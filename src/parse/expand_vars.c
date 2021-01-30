/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:48:16 by valentin          #+#    #+#             */
/*   Updated: 2021/01/30 18:50:41 by valentin         ###   ########.fr       */
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
	slice = ft_strslice(tok->str, *i + 1, j); // Protect
	val = get_envval(slice, shell->env);
	free(slice);
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
	*i = *i - 1 + ft_strlen(val); // PROBLEM ID VALUE IS INFERIOR !
}

void	expand_exit_code(t_tok *tok, int *i, t_shell *shell)
{
	char	*str_exit_code;
	int		tok_str_size;
	int		str_exit_code_size;
	int		nstr_size;
	char	*nstr;

	tok_str_size = ft_strlen(tok->str);
	str_exit_code = ft_utoa((unsigned)shell->exit_code);
	str_exit_code_size = ft_strlen(str_exit_code);
	nstr_size = *i + str_exit_code_size + (tok_str_size - (*i + 2)) + 1;
	nstr = (char *)malloc(sizeof(char) * nstr_size); // TODO : PROTECT
	ft_memset(nstr, '\0', nstr_size);
	ft_memcpy(nstr, tok->str, *i);
	ft_memcpy(&(nstr[*i]), str_exit_code, str_exit_code_size);
	ft_memcpy(&(nstr[*i + str_exit_code_size]), &(tok->str[*i + 2]), tok_str_size - (*i + 2));
	free(tok->str);
	tok->str = nstr;
	*i = *i - 1 + str_exit_code_size;
	free(str_exit_code);
}

void	expand_vars(t_tok *ltok, t_shell *shell)
{
	int		i;
	t_tok	*tmp;

	tmp = ltok;
	while (tmp)
	{
		if (tmp->type == txt || tmp->type == dquo)
		{
			i = 0;
			while (tmp->str[i])
			{
				if (tmp->str[i] == '$')
				{
					if (tmp->str[i + 1] && tmp->str[i + 1] == '?')
						expand_exit_code(tmp, &i, shell);
					else
						expand_var(tmp, &i, shell);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
