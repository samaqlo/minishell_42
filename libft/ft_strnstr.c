/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:02:42 by astalha           #+#    #+#             */
/*   Updated: 2022/10/26 04:51:50 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen (l))
		return ((char *)b);
	if (!b && len == 0)
		return (NULL);
	while (b[i] && i < len)
	{
		j = 0;
		while (b[i + j] == l[j] && i + j < len)
		{
			j++;
			if (!l[j])
				return ((char *)(b + i));
		}
		i++;
	}
	return (NULL);
}
