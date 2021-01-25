/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:21:20 by valentin          #+#    #+#             */
/*   Updated: 2021/01/25 17:29:40 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_cur_in(int fd, t_fds *fds)
{
	dup2(fds->cur_in, fd);
	close(fds->cur_in);
}

void	restore_cur_out(int fd, t_fds *fds)
{
	dup2(fds->cur_out, fd);
	close(fds->cur_out);
}
