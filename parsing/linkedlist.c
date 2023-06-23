/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:19:35 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	lastlst = ft_lstlast(*lst);
	lastlst->next = new;
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
		if (plst->type != space)
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
	if (!ft_strncmp(new->word, "|", ft_strlen(new->word)))
	{
		new->infos->n_pipes++;
		new->type = pi_pe;
	}
	else if (!ft_strncmp(new->word, ">", ft_strlen(new->word))
		|| !ft_strncmp(new->word, ">|", ft_strlen(new->word)))
		new->type = r_redirect;
	else if (!ft_strncmp(new->word, "<", ft_strlen(new->word)))
		new->type = l_redirect;
	else if (!ft_strncmp(new->word, ">>", ft_strlen(new->word)))
		new->type = append;
	else if (!ft_strncmp(new->word, "<<", ft_strlen(new->word)))
		new->type = here_doc;
	else
		new->type = word;
}

t_data	*ft_lstnew(char *content, t_infos *infos)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
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
	new->tfree = 0;
	new->fd_here_doc = -2;
	new->exp = 0;
	new->vars = NULL;
	new->next = NULL;
	return (new);
}
