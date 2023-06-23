/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:23:56 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 09:29:14 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int			i;
	int			l;
	char		*str;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
		i++;
	l = i;
	str = (char *) malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < l)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return ((char *)str);
}
