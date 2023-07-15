/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:39:15 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:47:44 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	space_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(" \t\n\v\f\r", str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	dollar_in(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 1)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	len_of_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_strchr(" \t\n\v\f\r", str[i]))
			i++;
		i++;
		j++;
	}
	j++;
	return (j);
}

char	*skip_space(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!space_in(str))
		return (str);
	tmp = malloc(len_of_space(str));
	while (str[i])
	{
		if ((ft_strchr(" \t\n\v\f\r", str[i]) && (!ft_strchr(" \t\n\v\f\r",
						str[i + 1]) || !str[i + 1]))
			|| !ft_strchr(" \t\n\v\f\r", str[i]))
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		else if (ft_strchr(" \t\n\v\f\r", str[i]))
			i++;
	}
	free(str);
	return (tmp);
}

char	*expand(t_list_env *env)
{
	if (!env->c)
		return (ft_strdup(""));
	else
		return (ft_strdup(env->content));
}
