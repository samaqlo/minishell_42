/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:21:42 by astalha           #+#    #+#             */
/*   Updated: 2023/06/19 16:53:55 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int glob_i  =0 ;
char    *get_tmp()
{
    char *name;
    char *suffix;
    int i;
    i = 1;

    suffix = ft_itoa(i);
    name = ft_strjoin("/tmp/.tmp", suffix);
    while (!access(name, F_OK))
    {
        free(name); 
        free(suffix);
        i++;
        suffix = ft_itoa(i);
        name = ft_strjoin("/tmp/.tmp", suffix);
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
void    c_handl(int sig)
{
    (void)sig;
   close(0);
}
void    fill_here_doc(int fd, t_data *del)
{
    char *input;
    char *expand;
    int  fd2;
    
    while (1)
    {
        signal(SIGINT, &c_handl);
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
    if(ttyname(0) == NULL)
    {
        fd2 = open(ttyname(2), O_RDWR);
        dup2(0, fd2);
    }
    free(input);
}
t_data  *join_del(t_data *lst_words)
{
    char *str;
    t_data *tmp;
    t_infos *infos;
    char *temp = ft_strdup("");
    infos = lst_words->infos;
    while(lst_words && lst_words->type <= dq_word)
    {
        str = ft_strjoin(temp, lst_words->word);
        free(temp);
        temp = str;
        lst_words = lst_words->next;
    }
    tmp = ft_lstnew(str, infos);
    tmp->type = 1;
    tmp->tfree = 1;
    return (tmp);
}
t_data *get_del(t_data    *lst_words)
{
    lst_words = lst_words->next;
    while(lst_words->type == space)
        lst_words = lst_words->next;
    if(lst_words->type == word && (!lst_words->next || lst_words->next->type > dq_word))
        return (lst_words);
    // printf("%d\n", lst_words->type);
    return (join_del(lst_words)); 
}
void    here_doc_func(t_data *lst_words)
{
    int i;
    char *name;
    t_data *tmp;
    i = 0;
    set_ids(lst_words);
    if (!count_hrdc(lst_words))
        return;
    while (lst_words)
    {
        if (lst_words->type == here_doc)
            {
                name  = get_tmp();
                 lst_words->fd_here_doc = open(name, O_CREAT | O_RDWR, 0777);
                 tmp = get_del(lst_words); 
                fill_here_doc(lst_words->fd_here_doc, tmp);
                close(lst_words->fd_here_doc);
                 lst_words->fd_here_doc = open(name, O_RDONLY, 0444);
                 lst_words->infos->fds[lst_words->infos->index] = lst_words->fd_here_doc;
                 lst_words->infos->index++;
                free(name);
                if (tmp->tfree)
                {
                    free(tmp->word);
                    free(tmp);
                }
            }
        lst_words = lst_words->next;
    }
}
