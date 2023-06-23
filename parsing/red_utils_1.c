/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:53:19 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:58:11 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outred(t_cmd_lines *lines, int i)
{
	if (!ft_strcmp(lines->cmd_line[i + 1], ""))
		return (lines->outfile = -1, open_err(lines->cmd_line[i + 1], 0), 0);
	lines->outfile = open(lines->cmd_line[i + 1],
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	lines->infos->fds[lines->infos->index++] = lines->outfile;
	if (lines->outfile < 0)
	{
		g_global->exit_status = 1;
		return (open_err(lines->cmd_line[i + 1], 1), 0);
	}
	return (1);
}

int	appendred(t_cmd_lines *lines, int i)
{
	if (!ft_strcmp(lines->cmd_line[i + 1], ""))
		return (lines->outfile = -1, open_err(lines->cmd_line[i + 1], 0), 0);
	lines->outfile = open(lines->cmd_line[i + 1],
			O_CREAT | O_RDWR | O_APPEND, 0644);
	lines->infos->fds[lines->infos->index++] = lines->outfile;
	if (lines->outfile < 0)
	{
		g_global->exit_status = 1;
		return (open_err(lines->cmd_line[i + 1], 1), 0);
	}
	return (1);
}

int	redirections(t_cmd_lines *lines, int i)
{
	if (!ft_strcmp(lines->cmd_line[i], "<") && lines->cmd_line[i + 1])
	{
		if (!inred(lines, i))
			return (0);
	}
	else if (!ft_strcmp(lines->cmd_line[i], ">") && lines->cmd_line[i + 1])
	{
		if (!outred(lines, i))
			return (0);
	}
	else if (!ft_strcmp(lines->cmd_line[i], ">>") && lines->cmd_line[i + 1])
	{
		if (!appendred(lines, i))
			return (0);
	}
	return (1);
}

int	open_file(t_cmd_lines *lines)
{
	int	i;

	i = 0;
	while (lines->cmd_line[i])
	{
		if (is_red(lines->cmd_line[i]))
		{
			if (!redirections(lines, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	get_new_lenght(char **vars)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (vars[i])
	{
		if (is_red(vars[i]) && vars[i + 1])
			i += 2;
		if (vars[i])
		{
			len++;
			i++;
		}
	}
	return (len);
}
