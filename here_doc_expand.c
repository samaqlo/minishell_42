/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:05:04 by astalha           #+#    #+#             */
/*   Updated: 2023/06/04 11:28:54 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char     *expand_in_hd(char *str, t_list_env *env)
{
    int i;
    int j;
    int start;
    int len;
    char *word;
    i = 0;
    len  = 0;
    j = 0;
    char **vars = malloc((count_words(str) + 1) * sizeof(char *));
     while(str[i])
    {
        start = i;
        len = get_len(str, &i);
        word =  ft_substr(str, start, len);
        if (*word == '$')
            vars[j] = set_value(word, env);
        else
            vars[j] = ft_strdup(word);
        free(word);
        j++;
    }
    vars[j] = NULL;
    return (two_to_one(vars));
}
