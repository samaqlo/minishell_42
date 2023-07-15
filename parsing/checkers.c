/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:45:21 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:08:34 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redrect(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	is_built(t_cmd_lines *cmd)
{
	if (!cmd->cmd_line[0])
		return (0);
	if (!ft_strcmp(cmd->cmd_line[0], "echo") || !ft_strcmp(cmd->cmd_line[0],
			"ECHO"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "env") || !ft_strcmp(cmd->cmd_line[0],
			"ENV"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "pwd") || !ft_strcmp(cmd->cmd_line[0],
			"PWD"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->cmd_line[0], "exit"))
		return (1);
	return (0);
}
