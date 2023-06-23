/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 01:00:56 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 09:37:10 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_tmp(void)
{
	char	*name;
	char	*suffix;
	int		i;

	i = 1;
	suffix = ft_itoa(i);
	name = ft_strjoin("/tmp/.tmp", suffix);
	while (!access(name, F_OK))
	{
		free(name);
		free(suffix);
		i++;
		suffix = ft_itoa(i);
		name = ft_strjoin("/tmp/.tmp", suffix);
	}
	free(suffix);
	return (name);
}
int	count_hrdc(t_data *lst_words)
{
	int	count;

	count = 0;
	while (lst_words)
	{
		if (lst_words->type == here_doc)
			count++;
		lst_words = lst_words->next;
	}
	return (count);
}
void	c_handl(int sig)
{
	(void)sig;
	g_global->exit_status = 1;
	close(0);
}
void	sig_D(t_data *lst_words)
{
	int	fd2;

	close(lst_words->fd_here_doc);
	lst_words->fd_here_doc = -1;
	fd2 = open(ttyname(2), O_RDWR);
	dup2(0, fd2);
}
void	fill_here_doc(int fd, t_data *del, t_data *lst_words)
{
	char	*input;
	char	*expand;

	while (1)
	{
		signal(SIGINT, &c_handl);
		input = readline(">");
		if (!input || !ft_strcmp(input, del->word))
			break ;
		if (del->type == word && dollar_in(input))
		{
			expand = expand_in_hd(input, del->infos->env);
			ft_putstr_fd(expand, fd);
			free(expand);
		}
		else
			ft_putstr_fd(input, fd);
		ft_putchar_fd('\n', fd);
		free(input);
	}
	if (ttyname(0) == NULL)
		sig_D(lst_words);
	free(input);
}
