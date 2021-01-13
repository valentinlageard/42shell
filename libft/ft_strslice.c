/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:57:03 by valentin          #+#    #+#             */
/*   Updated: 2021/01/13 01:09:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strslice(char *str, int start, int end)
{
	char	*slice;

	if (start > end)
		return (NULL);
	if (start == end)
		return (ft_strdup(""));
	if (!(slice = (char *)malloc(sizeof(char) * ((end - start) + 1))))
		return (NULL);
	ft_strlcpy(slice, &str[start], (end - start) + 1);
	return (slice);
}
