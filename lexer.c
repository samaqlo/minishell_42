/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/04/30 22:10:08 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int quoting_checker(char *str, t_infos *infos)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    infos->n_pipes = 0;
    while(str[i])
    {
        if (str[i] == '\'')
        {
            if (!flag)
                flag = 1;
            else if (flag == 1)
                flag = 0;
        }
        else if (str[i] == '\"')
        {
            if (!flag)
                flag = 2;
            else if (flag == 2)
                flag = 0;
        } 
        i++;
    }
    return (flag);
}

int     quote_len(char *str, int flag, int *pos)
{
    int i;
    int len;

    i = 1;
    len = 0;
    while(str[i])
    {
        printf("[%c]\n", str[i]);
        if (str[i] == '\'' && flag == 1 && ft_strchr("|>< \t\n", str[i + 1]))
            return (len);
        else if (str[i] == '\"' && flag == 2 && ft_strchr("|>< \t\n", str[i + 1]))
            return (len);
        else if (str[i] == '\"' && flag == 2)
            i++;
        else if (str[i] == '\'' && flag == 1)
            i++;
        else
        {
            len++;
            i++;
        }
        *pos += i;
    }
    return (len);
}
void    lexer(char *str)
{
    int i;
    int flag;
    t_data *lst_words = NULL;
    
    i = 0;
    flag = 0;
    while (str[i])
    {
        
    }
    
}