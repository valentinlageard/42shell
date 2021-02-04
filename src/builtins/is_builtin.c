/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:55 by valentin          #+#    #+#             */
/*   Updated: 2021/02/03 22:22:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_str)
{
	if (!cmd_str[0])
		return (0);
	if (ft_strncmp(cmd_str, "exit", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "env", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "export", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "unset", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "pwd", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "echo", ft_strlen(cmd_str)) == 0)
		return (1);
	else if (ft_strncmp(cmd_str, "cd", ft_strlen(cmd_str)) == 0)
		return (1);
	else
		return (0);
}
