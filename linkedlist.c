/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/05/05 15:20:09 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*lastlst;

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
void	set_type(t_data *new)
{
	if (!ft_strncmp(new->word, "|",ft_strlen(new->word)))
		new->type = pi_pe;
	else if (!ft_strncmp(new->word, ">",ft_strlen(new->word)) || !ft_strncmp(new->word, ">|",ft_strlen(new->word)))
		new->type = r_redirect;
	else if (!ft_strncmp(new->word, "<",ft_strlen(new->word)))
		new->type = l_redirect;
	else if (!ft_strncmp(new->word, ">>",ft_strlen(new->word)))
		new->type = append;
	else if (!ft_strncmp(new->word, "<<",ft_strlen(new->word)))
		new->type = here_doc;
	else
		new->type = word;
		
}
t_data	*ft_lstnew(char *content, t_infos	*infos)
{
	t_data	*new;

	new = (t_data *) malloc (sizeof (t_data));
	if (!new)
		return (NULL);
	new->word = content;
	set_type(new);
	if (infos->flag == 1)
	{
		new->type = sq_word;
		infos->flag = 0;
	}
	else if (infos->flag == 2)
	{
		new->type = dq_word;
		infos->flag = 0;
	}
	new->infos = infos;
	new->next = NULL;
	return (new);
}
