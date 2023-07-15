/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_src1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:54:05 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:23:25 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 4);
		i++;
	}
	return (NULL);
}

char	*print_env(t_list_env **env, char *var)
{
	t_list_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var) && tmp->content && tmp->c)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	echo_status_func(char *str, long i, long *n)
{
	long long	hold;

	while (str[i] >= '0' && str[i] <= '9')
	{
		hold = *n;
		*n = *n * 10 + str[i] - 48;
		if (hold != *n / 10)
			g_global->echo_status = 1;
		else
			g_global->echo_status = 0;
		i++;
	}
	if (!ft_strcmp(str, "-9223372036854775808"))
		g_global->echo_status = 0;
}

long	ft_atoi_overflow(char *str)
{
	long	i;
	long	n;
	int		signe;

	i = 0;
	n = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	echo_status_func(str, i, &n);
	return (n * signe);
}
