/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 02:34:01 by astalha           #+#    #+#             */
/*   Updated: 2022/10/24 03:17:40 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen (s);
	str = malloc (len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f (i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
