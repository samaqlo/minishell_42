/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:03:52 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/17 20:10:46 by astalha          ###   ########.fr       */
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
	//i case u delet SHLVL it should start with 1
	if (!shlvl)
	{
		shlvl = ft_strdup("1");
		ft_lstadd_back_env(enev, ft_lstnew_env(shlvl, "SHLVL", 1));
		return ;
	}
	shlvl_i = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(shlvl_i);
	change_env(enev, "SHLVL", shlvl);
	free(shlvl);
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
		content = getcwd(NULL, 0);
		ft_lstadd_back_env(enev, ft_lstnew_env(content, "PWD", 1));
		ft_lstadd_back_env(enev, ft_lstnew_env("/usr/bin/env", "_", 1));
		shell_env(enev);
		ft_lstadd_back_env(enev,
				ft_lstnew_env("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.",
					"PATH", 3));
		free (content);
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
	t_list_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, var) && tmp->content && tmp->c)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

long ft_atoi_overflow(char *str)
{
	long	i;
	long	n;
	int	signe;
	long long hold;

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
	while (str[i] >= '0' && str[i] <= '9')
	{
		hold = n;
		n = n * 10 + str[i] - 48;
		if(hold != n / 10)
			g_global->echo_status = 1;
		else
			g_global->echo_status = 0;
		i++;
	}
	if (!ft_strcmp(str, "-9223372036854775808"))
		g_global->echo_status = 0;
	return (n * signe);
}