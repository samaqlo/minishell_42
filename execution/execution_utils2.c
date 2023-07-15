/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:26:35 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 16:24:11 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_split(t_cmd_lines *cmd)
{
	char	**split;
	char	*path;
	char	*res;
	char	*str;

	if (access(cmd->cmd_line[0], F_OK) == 0 && (ft_strrchr(cmd->cmd_line[0],
				'/') || !access(cmd->cmd_line[0], X_OK)))
		return (cmd->cmd_line[0]);
	path = print_env(&cmd->infos->env, "PATH");
	if (!path)
		return (err_file(cmd->cmd_line[0]), NULL);
	split = ft_split(path, ':');
	str = join_args(cmd);
	res = get_binary(split, str);
	if (access(res, F_OK) || !ft_strcmp(cmd->cmd_line[0], ""))
	{
		err_cmd(cmd->cmd_line[0]);
		res = NULL;
	}
	free(str);
	freealloc2(split);
	return (res);
}

void	err_127(char *str, DIR *dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": is a directory\n", 2);
	closedir(dir);
	exit(127);
}

int	execve_fail(char *path, t_cmd_lines *lines)
{
	DIR	*dir;

	if (!path)
		exit(127);
	dir = opendir(path);
	if (dir)
		err_127(lines->cmd_line[0], dir);
	else if (errno == EACCES)
		return (perror("minishell"), exit(126), 0);
	else if (errno == ENOENT)
		perror("minishell");
	exit(127);
	return (1);
}

void	ft_wait(t_cmd_lines *lines, int pid, int old, int fd)
{
	if (!lines)
		waitpid(pid, &g_global->exit_status, 0);
	close(old);
	close(fd);
}

void	fds_manager(t_cmd_lines *lines, int *fd, int old)
{
	if (old != -1)
	{
		dup2(old, 0);
		close(old);
	}
	if (lines->next)
		dup2(fd[1], 1);
	if (lines->outfile > 2)
		dup2(lines->outfile, 1);
	if (lines->infile > 2)
		dup2(lines->infile, 0);
	close(fd[1]);
	close(fd[0]);
	if (!lines->cmd_line[0] || lines->cmd_line[0])
	{
		if (lines->infile < 0 || lines->outfile < 0)
			exit(1);
		else if (!lines->cmd_line[0])
			exit(0);
	}
}
