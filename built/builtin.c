/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/06/20 23:53:42 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_echo(char **av, int fd)
{
	int	i;
	int	test;

	i = 1;
	test = 1;
	// echo "" test --> env 
	if(!av[1] || (!ft_strcmp(av[1], "")))
	{
		ft_putstr_fd("\n", fd);
		return(1);
	}
	while (av[i])
	{
		if (av[i][0])
		{
			if (check_n(av[i]))
			{
				ft_putstr_fd(av[i], fd);
				test = 0;
				if (av[i + 1])
					ft_putstr_fd(" ", fd);
			}
			if (!test && !check_n(av[i]))
			{
				ft_putstr_fd(av[i], fd);
				if (av[i + 1])
					ft_putstr_fd(" ", fd);
			}
		}
		i++;
	}
	if (av[1] && check_n(av[1]))
		ft_putstr_fd("\n", fd);
	return (1);
}

// unset don't remove $pwd $old_pwd $HOME
int	built_env(t_list_env *enev, int fd)
{
	while (enev)
	{
		if (enev->c == 1 && enev->content)
		{
			ft_putstr_fd(enev->variable, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(enev->content, fd);
			ft_putstr_fd("\n", fd);
		}
		enev = enev->next;
	}
	return (1);
}

int	parse_unset(char *unset)
{
	int i = 0;
	if(unset[0] != '_' && !ft_isalpha(unset[0]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(unset, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while(unset[i])
	{
		if (unset[i] != '_' && !ft_isalpha(unset[i]) && !isdigit(unset[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(unset, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	built_unset(t_list_env *enev, char **av)
{
	int			i;
	t_list_env	*head;

	i = 1;
	head = enev;
	while (av[i])
	{
		parse_unset(av[i]);
		while (enev)
		{
			if (!ft_strcmp(av[i], enev->variable))
				enev->c = 0;
			enev = enev->next;
		}
		enev = head;
		i++;
	}
	return (1);
}

int	built_pwd(t_list_env **env, int fd)
{
	char	str[1024];

	(void)env;
	if (getcwd(str, sizeof(str)))
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd(print_env(env, "PWD"), fd);
	return (1);
}
int	built_exit(t_cmd_lines *cmd, int flag)
{
	int i = 0;
	long res;

	if (!flag)
		exit(0);
	if (cmd->cmd_line[0] && !cmd->cmd_line[1])
	{

		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (!ft_strcmp(cmd->cmd_line[1], ""))
	{
		ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd->cmd_line[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
	}
	if(cmd->cmd_line[1])
	{
		if(cmd->cmd_line[1][0] == '-' || cmd->cmd_line[1][0] == '+')
			i++;
		while(cmd->cmd_line[1][i])
		{
			if(!ft_isdigit(cmd->cmd_line[1][i]))
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(cmd->cmd_line[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			i++;
		}
	}
	if (cmd->cmd_line[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	res = ft_atoi_overflow(cmd->cmd_line[1]);
	if(g_global->echo_status == 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd_line[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (g_global->echo_status == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(res);
	}
	return(1);
}

int	builts_in(t_cmd_lines *cmd, t_list_env **enev, int flag)
{
	int	i;
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (0);
	if (cmd && cmd->cmd_line && cmd->cmd_line[0])
	{
		i = 0;
		if (!ft_strcmp(cmd->cmd_line[0], "echo") || !ft_strcmp(cmd->cmd_line[0],
				"ECHO"))
			return(built_echo(cmd->cmd_line, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "env")
				|| !ft_strcmp(cmd->cmd_line[0], "ENV"))
			return(built_env(*enev, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "pwd")
				|| !ft_strcmp(cmd->cmd_line[0], "PWD"))
			return(built_pwd(enev, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "unset"))
			return(built_unset(*enev, cmd->cmd_line));
		else if (!ft_strcmp(cmd->cmd_line[0], "cd"))
			return(built_cd(*enev, cmd->cmd_line));
		else if (!ft_strcmp(cmd->cmd_line[0], "export"))
			return(built_export(*enev, cmd->cmd_line, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "exit"))
			return(built_exit(cmd, flag));
		// while (cmd->cmd_line[i])
		// {
		// 	free(cmd->cmd_line[i]);
		// 	cmd->cmd_line[i] = NULL;
		// 	i++;
		// }
		// free(cmd->cmd_line);
	}
	return (3);
}
