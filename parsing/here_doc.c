/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:21:42 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:50:43 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*join_del(t_data *lst_words)
{
	char	*str;
	t_data	*tmp;
	t_infos	*infos;
	char	*temp;

	temp = ft_strdup("");
	infos = lst_words->infos;
	while (lst_words && lst_words->type <= dq_word)
	{
		str = ft_strjoin(temp, lst_words->word);
		free(temp);
		temp = str;
		lst_words = lst_words->next;
	}
	tmp = ft_lstnew(str, infos);
	tmp->type = 1;
	tmp->tfree = 1;
	return (tmp);
}

t_data	*get_del(t_data *lst_words)
{
	lst_words = lst_words->next;
	while (lst_words->type == space)
		lst_words = lst_words->next;
	if (lst_words->type == word && (!lst_words->next
			|| lst_words->next->type > dq_word))
		return (lst_words);
	return (join_del(lst_words));
}

void	here_doc_exec(t_data *lst_words)
{
	char	*name;
	t_data	*tmp;

	name = get_tmp();
	lst_words->fd_here_doc = open(name, O_CREAT | O_RDWR, 0777);
	tmp = get_del(lst_words);
	fill_here_doc(lst_words->fd_here_doc, tmp, lst_words);
	if (lst_words->fd_here_doc > 0)
	{
		close(lst_words->fd_here_doc);
		lst_words->fd_here_doc = open(name, O_RDONLY, 0444);
		lst_words->infos->fds[lst_words->infos->index] = lst_words->fd_here_doc;
		lst_words->infos->index++;
	}
	free(name);
	if (tmp->tfree)
	{
		free(tmp->word);
		free(tmp);
	}
}

void	here_doc_func(t_data *lst_words)
{
	set_ids(lst_words);
	if (!count_hrdc(lst_words))
		return ;
	while (lst_words)
	{
		if (lst_words->type == here_doc)
			here_doc_exec(lst_words);
		lst_words = lst_words->next;
	}
}
