/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_src2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:05:40 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/21 17:09:29 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env(t_list_env **env, char *var, char *cont)
{
	t_list_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var))
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = NULL;
			if (!cont)
				tmp->content = ft_strdup("");
			else
				tmp->content = ft_strdup(cont);
		}
		if (tmp->c == 3)
			tmp->c = 1;
		tmp = tmp->next;
	}
}

int	check_env(t_list_env *env, char *var)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(env->variable, var) && env->c)
			return (i);
		i++;
		env = env->next;
	}
	return (0);
}

int	pars_export(char *av)
{
	int	i;

	i = 0;
	if (av[0] != '_' && ft_isalpha(av[0]) == 0)
		return (0);
	while (av[i] && av[i] != '=')
	{
		if (av[i] == '+' && av[i + 1] == '=')
			return (1);
		if (av[i] != '_' && ft_isalnum(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
