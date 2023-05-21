/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 02:26:43 by astalha           #+#    #+#             */
/*   Updated: 2022/10/21 01:24:41 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	size_t		l1;
	size_t		l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen (s1);
	l2 = ft_strlen (s2);
	ptr = malloc(l1 + l2 + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy (ptr, s1, l1 + 1);
	ft_strlcpy (ptr + l1, s2, l2 + 1);
	return (ptr);
}
