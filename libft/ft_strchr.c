/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:01:26 by astalha           #+#    #+#             */
/*   Updated: 2023/05/08 14:12:22 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(const char *s, int c)
{
	char		ch;
	int			i;

	i = 0;
	ch = (char) c;
	if (!ch)
		return (0);
	while (s[i])
	{
		if (s[i] == ch)
			return (1);
		i++;
	}
	return (0);
}
