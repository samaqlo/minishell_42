/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/20 23:50:51 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**convert_env(t_list_env *env, char **envp)
{
	int			i;
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

char	*path_split(t_cmd_lines *cmd)
{
	
	char	**split;
	char	*path;
	char	*res;
	char	*str;
	int		i;

	i = 0;
	if (access(cmd->cmd_line[0], F_OK) == 0 && ft_strrchr(cmd->cmd_line[0], '/'))
		return (cmd->cmd_line[0]);
	path = print_env(&cmd->infos->env, "PATH");
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		res = NULL;
	}
	free(str);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (res);
}

int	ft_execution(t_cmd_lines *lines, int fd[2])
{
	char	*path;
	pid_t	pid;
	int		old;
	char	**envp = NULL;
	DIR *dir;

	old = fd[0];
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		
		if (old != -1)
		{
			dup2(old, 0);
			close(old);
		}
		if (lines->next)
			dup2(fd[1], 1);
		if(lines->outfile > 2)
			dup2(lines->outfile, 1);
		if(lines->infile > 2)
			dup2(lines->infile, 0);
		close(fd[1]);
		close(fd[0]);
		// if (lines->infile > 2)
		// 	close(lines->infile);
		// if (lines->outfile > 2)
		// 	close(lines->outfile);
		if (!lines->cmd_line[0] || lines->cmd_line[0])
			{
				if (lines->infile < 0 || lines->outfile < 0)
				{
					exit(1);
				}
				else if (!lines->cmd_line[0])
					exit(0);
			}
		if (builts_in(lines, &lines->infos->env, 0) == 1)
			exit(0);
		envp = convert_env(lines->infos->env, envp);
		path = path_split(lines);
		if (execve(path, lines->cmd_line, envp) < 0)
		{
			if (!path)
				exit(127);
			//anjme3 hadchi f function
			dir = opendir(path);
			if(dir)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(lines->cmd_line[0], 2);
				ft_putstr_fd(": is a directory\n", 2);
				closedir(dir);
				exit(127);
			}
			else if (errno == EACCES)
			{
				perror("minishell");
				exit(126);
			}
			else if (errno == ENOENT)
				perror("minishell");
			// perror("minishell");
			exit(127);
		}
	}
	else
	{
		if(!lines->next)
			waitpid(pid, &g_global->exit_status, 0);
		close(old);
		close(fd[1]);
	}
	return (1);
}
