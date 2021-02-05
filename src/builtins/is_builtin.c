/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:55 by valentin          #+#    #+#             */
/*   Updated: 2021/02/05 12:40:43 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_str)
{
	int	c_len;

	c_len = ft_strlen(cmd_str);
	if (!ft_strncmp(cmd_str, "exit", c_len) && c_len == 4)
		return (1);
	else if (!ft_strncmp(cmd_str, "env", c_len) && c_len == 3)
		return (1);
	else if (!ft_strncmp(cmd_str, "export", c_len) && c_len == 6)
		return (1);
	else if (!ft_strncmp(cmd_str, "unset", c_len) && c_len == 5)
		return (1);
	else if (!ft_strncmp(cmd_str, "pwd", c_len) && c_len == 3)
		return (1);
	else if (!ft_strncmp(cmd_str, "echo", c_len) && c_len == 4)
		return (1);
	else if (!ft_strncmp(cmd_str, "cd", c_len) && c_len == 2)
		return (1);
	return (0);
}
