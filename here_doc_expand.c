/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:05:04 by astalha           #+#    #+#             */
/*   Updated: 2023/06/21 17:10:39 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_in_hd(char *str, t_list_env *env)
{
	int		i;
	int		j;
	int		start;
	int		len;
	char	*word;
	char	**vars;

	i = 0;
	len = 0;
	j = 0;
	vars = malloc((count_words(str) + 1) * sizeof(char *));
	while (str[i])
	{
		start = i;
		len = get_len(str, &i);
		word = ft_substr(str, start, len);
		if (!ft_strcmp("$", word))
			vars[j] = ft_strdup(word);
		else if (*word == '$')
			vars[j] = set_value(word, env);
		else
			vars[j] = ft_strdup(word);
		j++;
		free(word);
	}
	vars[j] = NULL;
	word = two_to_one(vars);
	freealloc2(vars);
	return (word);
}
