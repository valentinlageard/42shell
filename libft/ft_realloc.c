/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:10:17 by valentin          #+#    #+#             */
/*   Updated: 2020/11/27 16:41:39 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (size > 0)
	{
		if (!(new_ptr = malloc(size)))
			return (NULL);
	}
	if (ptr)
	{
		new_ptr = ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}
