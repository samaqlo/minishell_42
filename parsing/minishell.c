/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 16:08:59 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global	*g_global;

void	sig_handl(int sig)
{
	if (sig == SIGINT && waitpid(-1, NULL, WNOHANG))
	{
		g_global->exit_status = 1;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	init_env(t_infos *infos, char **env)
{
	infos->env = NULL;
	g_global = malloc(sizeof(t_global));
	g_global->exit_status = 0;
	grep_env(env, &infos->env);
}

int	protection(char *str)
{
	if (str && !*str)
	{
		free(str);
		return (0);
	}
	else if (!str)
	{
		ft_putstr_fd("\033[11C\033[1Aexit\n", 1);
		free(str);
		exit(0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_infos	infos;
	char	*str;

	(void)ac;
	(void)av;
	if (!ttyname(0))
		return (ft_putstr_fd("Error\n", 2), 0);
	init_env(&infos, env);
	if (!av[1])
	{
		while (1)
		{
			signal(SIGINT, &sig_handl);
			signal(SIGQUIT, &sig_handl);
			rl_catch_signals = 0;
			str = readline("tby_shell$ ");
			if (!protection(str))
				continue ;
			else
				tby_shell(str, &infos);
		}
	}
}
