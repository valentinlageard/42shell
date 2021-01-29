/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:34:12 by valentin          #+#    #+#             */
/*   Updated: 2021/01/29 14:34:13 by valentin         ###   ########.fr       */
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
