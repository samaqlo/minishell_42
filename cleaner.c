/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:22 by astalha           #+#    #+#             */
/*   Updated: 2023/06/15 16:21:47 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freealloc2(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr[i])
		i++;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free(ptr);
}
void     clean_list(t_data   **lst_words)
{
    t_data	*words;
	t_data	*tmp;

	if (!lst_words)
		return ;
	words = *lst_words;
	while (words)
	{
		tmp = words;
		words = words->next;
		// freealloc2(tmp->vars);
		free(tmp->word);
		free(tmp);
	}
	*lst_words = NULL;
}
