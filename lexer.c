/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/05/03 17:05:30 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int quoting_checker(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
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

    i = (*pos) + 1;
    len = 0;
    while(str[i])
    {
        if (str[i] == '\'' && flag == 1 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2)
            i++;
        else if (str[i] == '\'' && flag == 1)
            i++;
        else
        {
            len++;
            i++;
        }
    }
        i++;
        *pos = i;
    return (len);
}
int word_len(char *str, int *pos, int *is_quote)
{
    int i;
    int len = 0;

    i = *pos;
    while(ft_strchr(" \t\n\v\f\r", str[i]))
        i++;
    while(str[i])
    {
        if (*is_quote == 0 && str[i] == '\'')
            return (*pos = i, *is_quote = 1, quote_len(str, 1, pos));
        else if (*is_quote == 0 && str[i] == '\"')
            return (*pos = i, *is_quote = 2, quote_len(str, 2, pos));
        else if (ft_strchr(" \t\n\v\f\r", str[i]))
            break;
        else if (ft_strchr("<>|", str[i + 1]) || ft_strchr("<>|", str[i]))
        {
            if (ft_strchr)
            len++;
            i++;
            break;
        }
            len++;
            i++;
    }
    *pos = i;
    return (len);
}

void    lexer(char *str)
{
    int i;
    int flag;
    t_data *lst_words = NULL;
    t_infos infos;
    
    i = 0;
    flag = 0;
    if (quoting_checker(str))
        return ;
    
    
}