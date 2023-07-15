/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:52:21 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:22:27 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_err_255(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

void	ifndegit(t_cmd_lines *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_line[1][0] == '-' || cmd->cmd_line[1][0] == '+')
		i++;
	while (cmd->cmd_line[1][i])
	{
		if (!ft_isdigit(cmd->cmd_line[1][i]))
			exit_err_255(cmd->cmd_line[1]);
		i++;
	}
}

int	built_exit(t_cmd_lines *cmd, int flag)
{
	int		i;
	long	res;

	i = 0;
	if (!flag)
		exit(0);
	if (cmd->cmd_line[0] && !cmd->cmd_line[1])
		return (ft_putstr_fd("exit\n", 2), exit(0), 0);
	if (!ft_strcmp(cmd->cmd_line[1], ""))
		exit_err_255(cmd->cmd_line[1]);
	if (cmd->cmd_line[1])
		ifndegit(cmd);
	if (cmd->cmd_line[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	res = ft_atoi_overflow(cmd->cmd_line[1]);
	if (g_global->echo_status == 1)
		exit_err_255(cmd->cmd_line[1]);
	if (g_global->echo_status == 0)
		return (ft_putstr_fd("exit\n", 2), exit(res), 0);
	return (1);
}
