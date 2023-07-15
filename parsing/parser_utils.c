/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:23:02 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:02:55 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_w(t_data *lst_words)
{
	int	count;

	count = 0;
	if (lst_words->type == space || lst_words->type == pi_pe)
		lst_words = lst_words->next;
	while (lst_words)
	{
		if (lst_words->type == pi_pe)
			return (count);
		if (lst_words->type != space)
		{
			if ((lst_words->type == dq_word || lst_words->type == word)
				&& !ft_strcmp(lst_words->word, "") && lst_words->exp)
				count--;
			count++;
		}
		lst_words = lst_words->next;
	}
	return (count);
}

char	*join(t_data *lst_words, int *id)
{
	char	*str;
	char	*temp;

	temp = ft_strdup("");
	while (lst_words && lst_words->type <= dq_word)
	{
		str = ft_strjoin(temp, lst_words->word);
		free(temp);
		temp = str;
		lst_words = lst_words->next;
	}
	if (lst_words)
		*id = lst_words->id;
	else
		*id = -1;
	return (str);
}

int	fill_vars3(t_data **lst_words, int *i, char **vars, int *fd)
{
	int	id;

	id = 0;
	if ((*lst_words)->fd_here_doc >= -1)
		*fd = (*lst_words)->fd_here_doc;
	if (((*lst_words)->type == dq_word || (*lst_words)->type == word)
		&& !ft_strcmp((*lst_words)->word, "") && (*lst_words)->exp)
	{
		(*lst_words) = (*lst_words)->next;
		return (1);
	}
	if ((*lst_words)->type <= dq_word)
	{
		vars[(*i)++] = join((*lst_words), &id);
		if (id < 0)
			return (0);
		while ((*lst_words)->id + 1 != id)
			(*lst_words) = (*lst_words)->next;
	}
	else
		vars[(*i)++] = ft_strdup((*lst_words)->word);
	return (-1);
}

void	initvr(t_data **head, int *i, int *fd, t_data *lst_words)
{
	*i = 0;
	*fd = STDIN_FILENO;
	*head = lst_words;
}
