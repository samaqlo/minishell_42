/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/06/19 15:34:55 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     all_spaces(t_data *words)
{
    while(words)
    {
        if (words->type != space)
            return (0);
        words = words->next;
    }
    return (1);
}
int quoting_checker(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while(str[i])
    {
        if (!flag && ft_strchr(";&", str[i]))
            return (print_error(2, 0), 3);
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
int     strat_end_checker(char *str)
{
    int i;

    i = 0;
    if (str[i] == '|')
        return (ft_putstr_fd("minishell: syntax error near unexpected token `|\'\n", 2), 0);
    i = ft_strlen(str) - 1;
    if (ft_strchr("><|", str[i]))
        return (ft_putstr_fd("minishell: syntax error near unexpected token `newline\'\n", 2), 0);
    return (1);
}
int     quote_len(char *str, t_infos *infos)
{
    int i;
    int len;

    i = infos->pos + 1;
    len = 0;
    while(str[i])
    {
        if (str[i] == '\'' && infos->is_quote == 1)
            break;
        else if (str[i] == '\"' && infos->is_quote == 2)
            break;
        else
        {
            len++;
            i++;
    }
    }
    i++;
    infos->pos = i;
    return (len);
}


int white_sp(char *str, t_infos *infos)
{
    int i = infos->pos;
    int len = 0;
    
    while(ft_strchr(" \t\n\v\f\r", str[i]))
    {
        len++;
        i++;
    }
    infos->flag = 3;
    infos->pos = i;
    return (len);
}
int word_len(char *str, t_infos *infos)
{
    int i;
    int len = 0;

    i = infos->pos;
    if (ft_strchr(" \t\n\v\f\r", str[i]))
        return (white_sp(str, infos));
    while(str[i])
    {
        if (ft_strchr("<>", str[i]) && !ft_strchr(" \t\n\v\f\r><|", str[i+1]))
            return ((infos->pos) = i + 1, 1);
        else if (!infos->is_finish && ft_strchr(" \t\n\v\f\r", str[i]))
            break;
        else if (!infos->is_quote && str[i] == '\'')
            return (infos->flag = 1, infos->pos = i, infos->is_quote = 1, quote_len(str, infos));
        else if (!infos->is_quote && str[i] == '\"')
            return (infos->flag = 2, infos->pos = i, infos->is_quote = 2, quote_len(str, infos));
        else if (!ft_strchr(" \t\n\v\f\r><|", str[i]) && (str[i + 1] == '\"' || str[i + 1] == '\''))
            return (infos->pos = i + 1, ++len);
        else if ((ft_strchr("<>|", str[i + 1]) || ft_strchr("|", str[i])) && str[i + 1])
        {
            if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
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
    infos->index = 0;
    infos->n_red = 0;
}
int     count_red(t_data *lst_words)
{
    int count = 0;
    while(lst_words)
    {
        if (lst_words->type >= r_redirect && lst_words->type <= append)
            count++;
        lst_words = lst_words->next;
    }
    return (count);
}
int     is_expandable(t_data *lst_words)
{
    char *val;

    while(lst_words && lst_words->type != pi_pe)
    {
        if ((lst_words->type == word || lst_words->type == dq_word) && dollar_in(lst_words->word))
            {
                if (lst_words->next && lst_words->next->type != space)
                    break;
                val = set_value(lst_words->word, lst_words->infos->env);
                if (!ft_strcmp(val, "") || (space_in(val) && val[ft_strlen(val) - 1] != ' '))
                    return (free(val), 0);
                else 
                    return (free(val), 1);
            }
            lst_words = lst_words->next;
    }
    return (1);
} 
char    *get_next_to_red(t_data    *lst_words)
{
    lst_words = lst_words->next;
    while(lst_words)
    {
        if (lst_words->type != space)
            return (lst_words->word);
        lst_words = lst_words->next;
    }
    return (NULL);
}

void    amb(t_data *lst_words)
{
    while(lst_words)
    {
        if (lst_words->type >= r_redirect && lst_words->type <= append && lst_words->type != here_doc && !is_expandable(lst_words))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(get_next_to_red(lst_words), 2);
            ft_putstr_fd(": ambiguous redirect\n", 2);
            while(lst_words && lst_words->type != pi_pe)
                lst_words = lst_words->next;
        }
        else
            lst_words = lst_words->next;
    }
}
void    fill_fds(int    *tab, int len)
{
    int i;

    i = 0;
    while(i < len)
    {
        tab[i] = -1;
        i++;
    }
}
t_data    *lexer(char *str, t_infos *infos)
{
    t_data *lst_words = NULL;
    t_data *tmp;
    int c;
    char *str1;

    c = quoting_checker(str);
    if (c == 2 || c == 1)
        return (ft_putstr_fd("quote opened\n", 2), NULL);
    else if (c == 3)
        return (NULL);
    init_args(infos);
    while(1)
    {
        infos->start = infos->pos;
        infos->len = word_len(str, infos);
        str1 = ft_substr_parse(str, infos);
        tmp = ft_lstnew(str1, infos);
        ft_lstadd_back(&lst_words, tmp);
        if (infos->is_finish)
        {
            free(tmp);
            break;
        }
    }
    t_data *head = lst_words;
    if (all_spaces(lst_words) || !syntaxe_checker(lst_words))
        return (free(str1), clean_list(&lst_words), NULL);
    amb(lst_words);
    // if (glob_i == 1)
    // {
    //    printf("%d",lst_words->infos->fds[0]);
       
    // }
    head = lst_words;
    if (count_red(lst_words) > 0)
    {
        lst_words->infos->fds = malloc(count_red(lst_words) * sizeof(int));
        lst_words->infos->n_red = count_red(lst_words);
        fill_fds(lst_words->infos->fds, lst_words->infos->n_red);
    }
    // while(lst_words)
    // {
    //     printf("[%s]  --> [%d]\n", lst_words->word, lst_words->type);
    //     lst_words = lst_words->next;
    // }
    free(str1);
    return (head);
}
