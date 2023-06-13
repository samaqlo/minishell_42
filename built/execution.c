/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/13 16:15:30 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_args(t_cmd_lines *cmd)
{
	char	*arg;

	// printf("cmd----- : %s\n", cmd->cmd_line[0]);
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
	path = print_env(&cmd->infos->env, "PATH");
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd(": command not found\n", 2);
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
// if (lines->cmd_line[0][0] == '$')
// 	lines->cmd_line[0] = print_env(&lines->infos->env, lines->cmd_line[0] + 1);
void	ft_execution(t_cmd_lines *lines, int fd[2])
{
	char	*path;
	pid_t	pid;
	int		status;
	int		old;

	// char *const args[] = {"ls", ".", NULL};
	path = path_split(lines);
	if (!path)
		return ;
	old = fd[0];
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
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
		close(fd[1]);
		close(fd[0]);
		execve(path, lines->cmd_line, NULL);
		// if (execve(path, lines->cmd_line, NULL) == -1)
		// 	perror("minishell");
	}
	else
	{
		waitpid(pid, &status, 0);
		close(old);
		close(fd[1]);
	}
	return ;
}
