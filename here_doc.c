/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:21:42 by astalha           #+#    #+#             */
/*   Updated: 2023/06/03 21:51:51 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_tmp()
{
    char *name;
    char *suffix;
    int i;
    i = 1;

    suffix = ft_itoa(i);
    name = ft_strjoin(".tmp", suffix);
    while (!access(name, F_OK))
    {
        free(name);
        free(suffix);
        i++;
        suffix = ft_itoa(i);
        name = ft_strjoin(".tmp", suffix);
    }
    free(suffix);
    return (name);
}
int     count_hrdc(t_data *lst_words)
{
    int count;
    count = 0;
    while (lst_words)
    {
        if (lst_words->type == here_doc)
            count++;
        lst_words = lst_words->next;
    }
    return (count);
}

void    fill_here_doc(int fd, t_data *del)
{
    char *input;
    char *expand;
    while (1)
    {
        input = readline(">");
        if (!input || !ft_strcmp(input, del->word))
            break;
        if (del->type == word && dollar_in(input))
        {
            expand  = expand_in_hd(input, del->infos->env);
            ft_putstr_fd(expand, fd);
            free(expand);
        }
        else
            ft_putstr_fd(input, fd);
        ft_putchar_fd('\n', fd);
        free(input);
    }
    free(input);
}
t_data *get_del(t_data    *lst_words)
{
    while(lst_words)
    {  here
        if (lst_words->)
        if (lst_words->type <= dq_word)
            return(lst_words);
        lst_words = lst_words->next;
    }  
    return NULL; 
}
void    here_doc_func(t_data *lst_words)
{
    int i;
    char *name;
    i = 0;
    set_ids(lst_words);
    if (!count_hrdc(lst_words))
        return;
    while (lst_words)
    {
        if (lst_words->type == here_doc)
            {
                name  = get_tmp();
                 lst_words->fd_here_doc = open(name, O_CREAT | O_RDWR, 777);
                fill_here_doc(lst_words->fd_here_doc, get_del(lst_words));
                free(name);
            }
        lst_words = lst_words->next;
    }
}