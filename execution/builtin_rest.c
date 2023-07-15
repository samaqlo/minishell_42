/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:09:26 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/23 17:08:14 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_export(t_list_env *env, char **av, int fd)
{
	t_norm	chars;
	int		i;

	chars.var = NULL;
	i = 1;
	if (!av[1])
		exprt_no_args(env, fd);
	while (av[i])
	{
		chars.var = ft_substr(av[i], 0, check_equal(av[i]));
		if (av[i][check_equal(av[i]) - 1] == '+')
		{
			free(chars.var);
			chars.var = ft_substr(av[i], 0, check_equal(av[i]) - 1);
		}
		chars.cont = ft_substr(av[i], check_equal(av[i]) + 1, (ft_strlen(av[i])
					- check_equal(av[i])));
		ft_export(av, i, &env, &chars);
		i++;
	}
	return (1);
}

int	no_args(t_list_env **env, char *str)
{
	if (!print_env(env, "HOME"))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (0);
	}
	chdir(print_env(env, "HOME"));
	change_env(env, "PWD", getcwd(str, sizeof(str)));
	return (1);
}

void	err_chdir(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Not a directory\n", 2);
}

int	built_cd(t_list_env *env, char **args)
{
	char	str[1024];

	change_env(&env, "OLDPWD", print_env(&env, "PWD"));
	if (!args[1])
	{
		if (!no_args(&env, str))
			return (0);
	}
	else if (access(args[1], F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(args[1], R_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (access(args[1], X_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else if (args[1])
	{
		if (chdir(args[1]) < 0)
			return (err_chdir(args[1]), 0);
		change_env(&env, "PWD", getcwd(str, sizeof(str)));
	}
	return (1);
}
