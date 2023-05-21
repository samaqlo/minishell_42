/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:32:19 by astalha           #+#    #+#             */
/*   Updated: 2022/10/27 04:27:11 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counttk(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (s[i + 1] == c || !s[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

static int	to_allocate(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	freealloc(char **ptr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free (ptr[i]);
		i++;
	}
	free(ptr);
}

static const char	*copy(char **ptr, const char *s, char c, int index)
{
	int	len;

	len = 0;
	len = to_allocate (s, c);
	ptr[index] = ft_substr (s, 0, len);
	if (!ptr[index])
	{
		freealloc (ptr, index);
	}
	return (s + len);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		index;
	int		word_count;

	index = 0;
	if (!s)
		return (NULL);
	word_count = counttk (s, c);
	ptr = (char **) malloc (sizeof(char *) * (word_count + 1));
	if (!ptr)
		return (NULL);
	while (*s && index < word_count)
	{
		if (*s != c)
		{
			s = copy (ptr, s, c, index);
			if (!s)
				return (NULL);
			index++;
		}
		s++;
	}
	ptr[index] = 0;
	return (ptr);
}
