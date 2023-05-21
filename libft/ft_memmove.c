/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:51:26 by astalha           #+#    #+#             */
/*   Updated: 2022/10/27 03:52:41 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (!dest && !src)
		return (NULL);
	else if (dest > src)
	{
		while (size-- > 0)
			*(char *)(dest + size) = *(char *)(src + size);
	}
	else
		ft_memcpy (dest, src, size);
	return (dest);
}
