/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/06/10 16:14:54 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_echo(char **av, int fd)
{
	int	i;
	int	test;

	i = 1;
	test = 1;
	while (av[i])
	{
		if (!check_n(av[i]))
		{
			test = 0;
			i++;
		}
		ft_putstr_fd( av[i++], fd);
		if (!av[i + 1])
			ft_putstr_fd(" ", fd);
	}
	if (test == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}

// unset don't remove $pwd $old_pwd $HOME
int	built_env(t_list_env *enev, int fd)
{
	while (enev)
	{
		if (enev->c)
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

int	built_unset(t_list_env *enev, char **av)
{
	int			i;
	t_list_env	*head;

	i = 1;
	head = enev;
	while (av[i])
	{
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

int	builts_in(t_cmd_lines *cmd, t_list_env **enev)
{
	int	i;

	if (cmd && cmd->cmd_line && cmd->cmd_line[0])
	{
		i = 0;
		if (!ft_strcmp(cmd->cmd_line[0], "echo") || !ft_strcmp(cmd->cmd_line[0],
				"ECHO"))
			built_echo(cmd->cmd_line, cmd->outfile);
		else if (!ft_strcmp(cmd->cmd_line[0], "env")
				|| !ft_strcmp(cmd->cmd_line[0], "ENV"))
			built_env(*enev, cmd->outfile);
		else if (!ft_strcmp(cmd->cmd_line[0], "pwd")
				|| !ft_strcmp(cmd->cmd_line[0], "PWD"))
			built_pwd(enev, cmd->outfile);
		else if (!ft_strcmp(cmd->cmd_line[0], "unset")
				|| !ft_strcmp(cmd->cmd_line[0], "UNSET"))
			built_unset(*enev, cmd->cmd_line);
		else if (!ft_strcmp(cmd->cmd_line[0], "cd")
				|| !ft_strcmp(cmd->cmd_line[0], "CD"))
			built_cd(*enev, cmd->cmd_line);
		else if (!ft_strcmp(cmd->cmd_line[0], "export")
				|| !ft_strcmp(cmd->cmd_line[0], "EXPORT"))
			built_export(*enev, cmd->cmd_line, cmd->outfile);
		while (cmd->cmd_line[i])
		{
			free(cmd->cmd_line[i]);
			cmd->cmd_line[i] = NULL;
			i++;
		}
		free(cmd->cmd_line);
	}
	return (0);
}
