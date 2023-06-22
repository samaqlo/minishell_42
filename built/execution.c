/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/22 20:21:13 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_env(t_list_env *env, char **envp, int i)
{
	t_list_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->c == 1)
			i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		if (env->c == 1)
		{
			envp[i] = ft_strjoin(env->variable, "=");
			if (env->content)
				envp[i] = ft_strjoin(envp[i], env->content);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*join_args(t_cmd_lines *cmd)
{
	char	*arg;

	arg = ft_strjoin("/", cmd->cmd_line[0]);
	return (arg);
}
void	err_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
void	err_cmd(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}
char	*path_split(t_cmd_lines *cmd, int i)
{
	char	**split;
	char	*path;
	char	*res;
	char	*str;

	if (access(cmd->cmd_line[0], F_OK) == 0 && ft_strrchr(cmd->cmd_line[0],
			'/'))
		return (cmd->cmd_line[0]);
	path = print_env(&cmd->infos->env, "PATH");
	if (!path)
		return (err_file(cmd->cmd_line[0]) ,NULL);
	split = ft_split(path, ':');
	str = join_args(cmd);
	while (split[i])
	{
		res = ft_strjoin(split[i], str);
		if (access(res, F_OK) == 0)
			break ;
		free(res);
		i++;
	}
	if (access(res, F_OK))
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
	DIR		*dir;

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

int	ft_execution(t_cmd_lines *lines, int fd[2])
{
	char	*path;
	pid_t	pid;
	int		old;
	char	**envp;

	envp = NULL;
	old = fd[0];
	if (pipe(fd) < 0)
		return (perror("pipe"), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 0);
	else if (pid == 0)
	{
		fds_manager(lines, fd, old);
		if (builts_in(lines, &lines->infos->env, 0) == 1)
			exit(0);
		envp = convert_env(lines->infos->env, envp, 0);
		path = path_split(lines, 0);
		if (execve(path, lines->cmd_line, envp) < 0)
			execve_fail(path, lines);
	}
	else
		ft_wait(lines->next, pid, old, fd[1]);
	return (1);
}
