/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tby_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:40:54 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:20:46 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_lines	*parsing(char *str, t_infos *infos)
{
	t_data		*lst_words;
	t_cmd_lines	*lines;

	lst_words = lexer(str, infos);
	if (!lst_words)
	{
		free(str);
		return (NULL);
	}
	here_doc_func(lst_words);
	the_fucking_expand(lst_words);
	lines = join_words(lst_words);
	if (!delete_adds(&lines) || !lines)
	{
		free(str);
		if (infos->n_red > 0)
			free(infos->fds);
		return (NULL);
	}
	return (lines);
}

void	ft_handle_status(void)
{
	if (WEXITSTATUS(g_global->exit_status))
		g_global->exit_status = WEXITSTATUS(g_global->exit_status);
	else if (WIFSIGNALED(g_global->exit_status))
		g_global->exit_status = WTERMSIG(g_global->exit_status) + 128;
}

void	execution(t_cmd_lines *lines, t_infos *infos, int c)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (!lines->next && is_built(lines))
	{
		c = builts_in(lines, &infos->env, 1);
		if (!c)
			g_global->exit_status = 1;
		else
			g_global->exit_status = 0;
	}
	else
	{
		while (lines)
		{
			if (!ft_execution(lines, fd))
				break ;
			lines = lines->next;
			ft_handle_status();
		}
	}
	while (wait(0) != -1)
		;
	close(fd[0]);
}

void	tby_shell(char *str, t_infos *infos)
{
	t_cmd_lines	*lines;

	add_history(str);
	lines = parsing(str, infos);
	if (!lines)
		return ;
	execution(lines, infos, 0);
	free(str);
	clean_lines2(&lines);
}
