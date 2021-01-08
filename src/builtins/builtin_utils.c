/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:36:23 by valentin          #+#    #+#             */
/*   Updated: 2021/01/08 16:45:42 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_str)
{
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
