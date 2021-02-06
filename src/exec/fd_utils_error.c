/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:28:44 by valentin          #+#    #+#             */
/*   Updated: 2021/02/06 16:29:47 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_close_fds(t_fds *fds)
{
	restore_parent_inout(fds);
	if (fds->first >= 0)
		close(fds->first);
	if (fds->last >= 0)
		close(fds->last);
}
