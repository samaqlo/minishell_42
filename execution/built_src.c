/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:03:52 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/23 13:22:56 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	shell_env(t_list_env **enev)
{
	char	*shlvl;
	int		shlvl_i;

	shlvl = print_env(enev, "SHLVL");
	if (!shlvl)
	{
		shlvl = ft_strdup("1");
		ft_lstadd_back_env(enev, ft_lstnew_env(shlvl, "SHLVL", 1));
		free(shlvl);
		return ;
	}
	shlvl_i = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(shlvl_i);
	change_env(enev, "SHLVL", shlvl);
	free(shlvl);
}

void	unset_env(t_list_env **enev)
{
	char	*content;

	content = getcwd(NULL, 0);
	ft_lstadd_back_env(enev, ft_lstnew_env(content, "PWD", 1));
	ft_lstadd_back_env(enev, ft_lstnew_env("/usr/bin/env", "_", 1));
	shell_env(enev);
	ft_lstadd_back_env(enev,
		ft_lstnew_env("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", "PATH",
			3));
	free(content);
}

void	grep_env(char **env, t_list_env **enev)
{
	int		i;
	int		len;
	int		len_eq;
	char	*content;
	char	*variable;

	i = 0;
	if (!env[0])
	{
		unset_env(enev);
		return ;
	}
	while (env[i])
	{
		len_eq = check_equal(env[i]);
		len = ft_strlen(env[i]);
		variable = ft_substr(env[i], 0, len_eq);
		content = ft_substr(env[i], len_eq + 1, ft_strlen(env[i]) - len_eq);
		ft_lstadd_back_env(enev, ft_lstnew_env(content, variable, 1));
		i++;
		free(variable);
		free(content);
	}
	ft_lstadd_back_env(enev, ft_lstnew_env("", "?", 0));
	shell_env(enev);
}

int	check_n(char *av)
{
	long	i;

	i = 1;
	if (av[0] && av[0] != '-')
		return (1);
	if (av[0] == '-' && !av[1])
		return (1);
	while (av[i])
	{
		if (av[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
