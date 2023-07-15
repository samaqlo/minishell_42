/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:34:59 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:09:42 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_parse(char const *s, t_infos *infos)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (infos->start >= (int)ft_strlen(s))
		return (NULL);
	if (infos->len > (int)ft_strlen(s))
		infos->len = (int)ft_strlen(s);
	ptr = malloc(infos->len + 1);
	if (!ptr)
		return (NULL);
	while (s[i] && i < infos->len)
	{
		while ((infos->is_quote == 1 && s[infos->start] == '\'')
			|| (infos->is_quote == 2 && s[infos->start] == '\"'))
			infos->start++;
		ptr[i++] = s[infos->start++];
	}
	ptr[i] = 0;
	if (infos->is_quote && (s[infos->start] == '\'' || s[infos->start] == '\"'))
		infos->is_quote = 0;
	return (ptr);
}
