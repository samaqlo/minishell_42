/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/05/26 15:14:58 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_exp(t_expand **lst, t_expand *new)
{
	t_expand	*lastlst;

	if (!new->word)
		{
			new->infos->is_finish = 1;
			return ;
		}
	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast (*lst);
	lastlst->next = new;
}

void	ft_lstadd_front_exp(t_expand **lst, t_expand *new)
{	
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize_exp(t_expand *lst)
{
	int		i;
	t_expand	*plst;

	i = 0;
	if (!lst)
		return (0);
	plst = lst;
	while (plst != NULL)
	{
		if (plst->type != space)
			i++;
		plst = plst->next;
	}
	return (i);
}

t_expand	*ft_lstlast_exp(t_expand *lst)
{
	t_expand	*plst;

	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

t_expand	*ft_lstnew_exp(char *content, t_infos	*infos)
{
	t_expand	*new;

	new = (t_expand *) malloc (sizeof (t_expand));
	if (!new)
		return (NULL);
	new->infos = infos;
	new->word = content;
	set_type(new);
	if (infos->flag == 1)
		new->type = sq_word;
	else if (infos->flag == 2)
		new->type = dq_word;
	else if (infos->flag == 3)
		new->type = space;
	infos->flag = 0;
	new->next = NULL;
	// free(content);
	return (new);
}
