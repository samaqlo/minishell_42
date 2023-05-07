/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:20:22 by astalha           #+#    #+#             */
/*   Updated: 2023/05/05 15:35:32 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void     clean_list(t_data   *lst_words)
{
    t_data  *tmp;

    while(lst_words)
    {
        tmp = lst_words;
        lst_words = lst_words->next;
        free(tmp);
    }   
    free(lst_words);
}