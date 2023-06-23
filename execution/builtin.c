/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:37:52 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:23:39 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	i;

	i = 0;
	if (unset[0] != '_' && !ft_isalpha(unset[0]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(unset, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while (unset[i])
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

	if (getcwd(str, sizeof(str)))
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		if (strcmp(print_env(env, "PWD"), ""))
			ft_putstr_fd(print_env(env, "PWD"), fd);
		else
			ft_putstr_fd(".", fd);
		ft_putstr_fd("\n", fd);
	}
	return (1);
}

int	builts_in(t_cmd_lines *cmd, t_list_env **enev, int flag)
{
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (0);
	if (cmd && cmd->cmd_line && cmd->cmd_line[0])
	{
		if (!ft_strcmp(cmd->cmd_line[0], "echo") || !ft_strcmp(cmd->cmd_line[0],
				"ECHO"))
			return (built_echo(cmd->cmd_line, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "env")
			|| !ft_strcmp(cmd->cmd_line[0], "ENV"))
			return (built_env(*enev, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "pwd")
			|| !ft_strcmp(cmd->cmd_line[0], "PWD"))
			return (built_pwd(enev, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "unset"))
			return (built_unset(*enev, cmd->cmd_line));
		else if (!ft_strcmp(cmd->cmd_line[0], "cd"))
			return (built_cd(*enev, cmd->cmd_line));
		else if (!ft_strcmp(cmd->cmd_line[0], "export"))
			return (built_export(*enev, cmd->cmd_line, cmd->outfile));
		else if (!ft_strcmp(cmd->cmd_line[0], "exit"))
			return (built_exit(cmd, flag));
	}
	return (3);
}
