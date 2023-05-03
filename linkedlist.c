/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/05/02 11:24:54 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast (*lst);
	lastlst->next = new;
}

void	ft_lstadd_front(t_data **lst, t_data *new)
{	
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_data *lst)
{
	int		i;
	t_data	*plst;

	i = 0;
	if (!lst)
		return (0);
	plst = lst;
	while (plst != NULL)
	{
		i++;
		plst = plst->next;
	}
	return (i);
}

t_data	*ft_lstlast(t_data *lst)
{
	t_data	*plst;

	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

t_data	*ft_lstnew(char *content)
{
	t_data	*new;

	new = (t_data *) malloc (sizeof (t_data));
	if (!new)
		return (NULL);
	new->word = content;
	new->type = word;
	new->next = NULL;
	return (new);
}
