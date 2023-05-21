/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrrchr_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:59:35 by ohaimad           #+#    #+#             */
/*   Updated: 2023/05/21 23:59:50 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr_env(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == c)
			return (ft_substr(s, 0, i));
		i--;
	}
	if (s[i] == c)
		return (ft_substr(s, 0, i));
	return (0);
}