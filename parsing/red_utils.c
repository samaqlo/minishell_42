/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:51:39 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:20:27 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_type(t_cmd_lines *line)
{
	int	i;

	i = 0;
	while (line->cmd_line[i])
	{
		if (!ft_strcmp(">", line->cmd_line[i]))
			return (r_redirect);
		else if (!ft_strcmp("<", line->cmd_line[i]))
			return (l_redirect);
		else if (!ft_strcmp(">>", line->cmd_line[i]))
			return (append);
		else if (!ft_strcmp("<<", line->cmd_line[i]))
			return (here_doc);
		i++;
	}
	return (0);
}

int	is_red(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("<>", str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_fd(int **fds, int fd)
{
	int	i;

	i = 0;
	while (*fds[i] != 0)
		i++;
	*fds[i] = fd;
}

int	priority(char **vars, int i)
{
	int	flag;

	flag = 0;
	while (vars[i])
	{
		if (!ft_strcmp(vars[i], "<<"))
			flag = 0;
		else if (!ft_strcmp(vars[i], "<"))
			flag = 1;
		i++;
	}
	return (flag);
}

int	inred(t_cmd_lines *lines, int i)
{
	int	fd;

	if (!ft_strcmp(lines->cmd_line[i + 1], ""))
		return (lines->infile = -1, open_err(lines->cmd_line[i + 1], 0), 0);
	fd = open(lines->cmd_line[i + 1], O_RDONLY, 0444);
	if (priority(lines->cmd_line, i))
		lines->infile = fd;
	lines->infos->fds[lines->infos->index++] = fd;
	if (lines->infile < 0)
	{
		g_global->exit_status = 1;
		return (open_err(lines->cmd_line[i + 1], 0), 0);
	}
	return (1);
}
