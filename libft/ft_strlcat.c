/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:41:09 by astalha           #+#    #+#             */
/*   Updated: 2022/10/24 01:35:02 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!dst && !size)
		return (0);
	if (size == 0)
		return (ft_strlen(src) + size);
	j = ft_strlen(dst);
	if (size < j)
		return (ft_strlen (src) + size);
	if (size > j + 1)
	{
		while (src[i] && i < size - j - 1)
		{
			dst[j + i] = (char)src[i];
			i++;
		}
		dst[j + i] = 0;
	}
	return (j + ft_strlen (src));
}
