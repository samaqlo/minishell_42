/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/23 12:45:50 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		path = path_split(lines);
		if (execve(path, lines->cmd_line, envp) < 0)
			execve_fail(path, lines);
	}
	else
		ft_wait(lines->next, pid, old, fd[1]);
	return (1);
}
