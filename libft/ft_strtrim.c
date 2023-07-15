/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:18:55 by astalha           #+#    #+#             */
/*   Updated: 2022/10/23 01:02:15 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	int			len;

	if (!s1 || !set)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	start = s1;
	end = s1 + len - 1;
	while (*start && ft_strchr (set, *start))
		start++;
	if (start == s1 + len)
		return (ft_strdup(""));
	while (*end && ft_strchr (set, *end))
		end--;
	end++;
	return (ft_substr(start, 0, end - start));
}
