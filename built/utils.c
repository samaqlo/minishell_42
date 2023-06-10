/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:00:24 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/09 23:12:19 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstlast_env(t_list_env *lst)
{
	t_list_env	*plst;

	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

void	ft_lstadd_back_env(t_list_env **lst, t_list_env *new)
{
	t_list_env	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast_env(*lst);
	lastlst->next = new;
}

t_list_env	*ft_lstnew_env(char *content, char *variable, int flag)
{
	t_list_env	*new;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (!new)
		return (NULL);
	new->variable = ft_strdup(variable);
	new->content = ft_strdup(content);
	new->c = flag;
	new->next = NULL;
	return (new);
}
