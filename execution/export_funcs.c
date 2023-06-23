/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:35:10 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:49:48 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exprt_no_args(t_list_env *env, int fd)
{
	while (env)
	{
		if (env->c == 1 && env->content)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env->variable, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->content, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else if (env->c == 1 && !env->content)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env->variable, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
}

void	concat(t_list_env **env, char *var, char *cont)
{
	char	*tmp;

	if (check_env(*env, var))
	{
		if (print_env(env, var))
		{
			tmp = ft_strjoin(print_env(env, var), cont);
			change_env(env, var, tmp);
			free(tmp);
		}
		else
		{
			tmp = ft_strjoin("", cont);
			change_env(env, var, tmp);
			free(tmp);
		}
	}
	else
		ft_lstadd_back_env(env, ft_lstnew_env(cont, var, 1));
}

void	set_var(t_list_env **env, char *var, char *cont)
{
	if (check_env(*env, var))
		change_env(env, var, cont);
	else
		ft_lstadd_back_env(env, ft_lstnew_env(cont, var, 1));
}

void	print_exprt_err(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	ft_export(char **av, int i, t_list_env **env, t_norm *chars)
{
	if (av[i] && !pars_export(av[i]))
		print_exprt_err(av[i]);
	else if (av[i] && check_equal(av[i]))
	{
		if (av[i][check_equal(av[i]) - 1] == '+')
			concat(env, chars->var, chars->cont);
		else
			set_var(env, chars->var, chars->cont);
	}
	else if (av[i] && !check_equal(av[i]))
	{
		if (!check_env(*env, av[i]))
			ft_lstadd_back_env(env, ft_lstnew_env(NULL, av[i], 1));
		else
			change_env(env, av[i], print_env(env, av[i]));
	}
	free(chars->var);
	free(chars->cont);
}
