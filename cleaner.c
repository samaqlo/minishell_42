/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:22 by astalha           #+#    #+#             */
/*   Updated: 2023/06/21 17:10:08 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freealloc2(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	// if (!ptr[i])
	// 	i++;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}
void	clean_list(t_data **lst_words)
{
	t_data	*words;
	t_data	*tmp;

	if (!lst_words)
		return ;
	words = *lst_words;
	while (words)
	{
		free(words->word);
		if (words->vars)
			freealloc2(words->vars);
		tmp = words;
		words = words->next;
		free(tmp);
	}
	// free(words);
	*lst_words = NULL;
}
void	clean_in_exit(t_list_env **env, t_global *g_global)
{
	t_list_env *tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->content);
		free(tmp->variable);
		free(tmp);
	}
	free(g_global);
}