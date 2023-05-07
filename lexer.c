/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/05/07 15:21:20 by astalha          ###   ########.fr       */
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

// void     pipes_checker(t_infos  *infos)
// {
    
// }

// void    check_the_$(char    *str)
// {
    
// }

int     quote_len(char *str, int flag, int *pos, int lenght)
{
    int i;
    int len;

    i = (*pos) + 1;
    len = 0;
    if (lenght)
        len += lenght;
    while(str[i])
    {
        if (str[i] == '\'' && flag == 1 && ft_strchr("|>< \t\n\v\f\r", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2 && ft_strchr("|>< \t\n\v\f\r", str[i + 1]))
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
int word_len(char *str, t_infos *infos)
{
    int i;
    int len = 0;

    i = infos->pos;
    while(ft_strchr(" \t\n\v\f\r", str[i]))
        i++;
    while(str[i])
    {
        if (ft_strchr("<>", str[i]) && !ft_strchr(" \t\n\v\f\r><|&", str[i+1]))
            return ((infos->pos) = i + 1, 1);
        else if (ft_strchr(" \t\n\v\f\r", str[i]))
            break;
        else if (!infos->is_quote && str[i] == '\'')
            return (infos->flag = 1, infos->pos = i, infos->is_quote = 1, quote_len(str, 1, &infos->pos, len));
        else if (!infos->is_quote && str[i] == '\"')
            return (infos->flag = 2, infos->pos = i, infos->is_quote = 2, quote_len(str, 2, &infos->pos, len));
        else if (ft_strchr("<>|", str[i + 1]) || ft_strchr("|", str[i]))
        {
            if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '|'))
            {
                len++;
                i++;
            }
            len++;
            i++;
            break;
        }
            len++;
            i++;

    }
    infos->pos = i;
    printf("%d\n", len);
    return (len);
}

void    init_args(t_infos *infos)
{
    infos->is_quote = 0;
    infos->is_finish = 0;
    infos->len = 0;
    infos->flag = 0;
    infos->n_pipes = 0;
    infos->pos = 0;
    infos->start = 0;
}
void    lexer(char *str)
{
    t_data *lst_words = NULL;
    t_infos infos;
    if (quoting_checker(str))
        return ;
    init_args(&infos);
    while(1)
    {
        infos.start = infos.pos;
        infos.len = word_len(str, &infos);
        ft_lstadd_back(&lst_words, ft_lstnew(ft_substr_parse(str, &infos), &infos));
            if (infos.is_finish)
                break;
    }
    while(lst_words)
    {
        printf("[%s]  --> [%d]\n", lst_words->word, lst_words->type);
        lst_words = lst_words->next;
    }
    clean_list(lst_words);
}
