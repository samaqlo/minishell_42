/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/05/27 19:59:25 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_exp(t_expand **lst, t_expand *new)
{
	t_expand	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast_exp(*lst);
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
		plst = plst->next;
		i++;
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

t_expand	*ft_lstnew_exp(char *content)
{
	t_expand	*new;

	new = (t_expand *) malloc (sizeof (t_expand));
	if (!new)
		return (NULL);
	new->exp = 0;
	new->word = content;
	new->next = NULL;
	return (new);
}
