/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:22 by astalha           #+#    #+#             */
/*   Updated: 2023/05/21 16:10:21 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(tmp->word);
		free(tmp);
	}
	*lst_words = NULL;
}