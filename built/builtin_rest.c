/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:09:26 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/12 22:38:52 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_export(t_list_env *env, char **av, int fd)
{
	char	*var;
	char	*cont;
	char	*plus;
	int		i;

	i = 1;
	if (!av[1])
	{
		while (env)
		{
			if (env->c && env->content)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(env->variable, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(env->content, fd);
				ft_putstr_fd("\n", fd);
				// ft_putstr_fd("declare -x %s=\"%s\"\n", env->variable, env->content);
			}
			else if (env->c && !env->content)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(env->variable, fd);
				ft_putstr_fd("\n", fd);
			}
			env = env->next;
		}
	}
	while (av[i])
	{
		plus = ft_strrchr_env(av[i], '+');
		if (plus)
			var = ft_substr(av[i], 0, check_equal(av[i]) - 1);
		else
			var = ft_substr(av[i], 0, check_equal(av[i]));
		cont = ft_substr(av[i], check_equal(av[i]) + 1, (ft_strlen(av[i])
					- check_equal(av[i])));
		if (av[i] && !pars_export(av[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			// ft_putstr_fd("minishell: export: `%s': not a valid identifier\n", av[i]);
		}
		else if (av[i] && check_equal(av[i]) && !plus)
		{
			if (check_env(env, var))
				change_env(&env, var, cont);
			else
				ft_lstadd_back_env(&env, ft_lstnew_env(cont, var, 1));
		}
		else if (av[i] && plus)
		{
			if (check_env(env, var))
			{
				if (print_env(&env, var))
					change_env(&env, var, ft_strjoin(print_env(&env, var), cont));
				else
					change_env(&env, var, ft_strjoin("", cont));
			}
			else
				ft_lstadd_back_env(&env, ft_lstnew_env(cont, var, 1));
		}
		else if (av[i] && !check_equal(av[i]))
		{
			if (!check_env(env, av[i]))
				ft_lstadd_back_env(&env, ft_lstnew_env(NULL, av[i], 1));
		}
		free(var);
		free(cont);
		i++;
	}
	return (1);
}

int	built_cd(t_list_env *env, char **args)
{
	char	str[1024];

	change_env(&env, "OLDPWD", print_env(&env, "PWD"));
	if (!args[1])
	{
		if (!print_env(&env, "HOME"))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (0);
		}
		chdir(print_env(&env, "HOME"));
		change_env(&env, "PWD", getcwd(str, sizeof(str)));
	}
	else if (access(args[1], F_OK) == -1)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (access(args[1], R_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (access(args[1], X_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (args[1])
	{
		chdir(args[1]);
		change_env(&env, "PWD", getcwd(str, sizeof(str)));
	}
	return (1);
}
