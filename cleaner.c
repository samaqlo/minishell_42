/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:22 by astalha           #+#    #+#             */
/*   Updated: 2023/06/16 02:24:01 by astalha          ###   ########.fr       */
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
	// free(lst_words);
	*lst_words = NULL;
}