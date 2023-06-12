/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:28:17 by astalha           #+#    #+#             */
/*   Updated: 2023/06/12 23:38:35 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_w(t_data *lst_words)
{
    int count;

    count = 1;
    if (lst_words->type == space || lst_words->type == pi_pe)
        lst_words = lst_words->next;
    while (lst_words)
    {
        if (lst_words->type == pi_pe)
            return (count);
        if (lst_words->type == space)
            count++;
        lst_words = lst_words->next;
    }
    return (count);
}
char    *join(t_data *lst_words, int *id)
{
    char *str;

    str = ft_strdup("");
    while(lst_words && lst_words->type  <= dq_word)
    {
        str = ft_strjoin(str, lst_words->word);
        lst_words = lst_words->next;
    }
    if (lst_words)
        *id = lst_words->id;
    else
        *id = -1;
    return str;
}
void    fill_vars(t_data *lst_words, t_cmd_lines **p_to_e)
{
    char **vars;
    t_data *head = lst_words;
    int id;
    int fd;
     int i;

    i = 0;
    id = 0;
    
    fd = STDIN_FILENO;
     vars = (char **)malloc((count_w(lst_words) + 1) * sizeof(char *));
     if (lst_words->type == pi_pe)
        lst_words = lst_words->next;
     while (lst_words && lst_words->type != pi_pe)
     {
        if (lst_words->type != space)
        {
            if (lst_words->fd_here_doc > 0)
                fd = lst_words->fd_here_doc;
            if (lst_words->type <= dq_word)
            {
                vars[i] = join(lst_words, &id);
            i++;
            if (id < 0)
                break;
            while (lst_words->id + 1 != id)
                lst_words = lst_words->next;
            }
            else
                {
                    vars[i] = ft_strdup(lst_words->word);
                    i++;
                }
        }
        lst_words = lst_words->next;
     }
     vars[i] = NULL;

     ft_lstadd_back_exp(p_to_e, ft_lstnew_exp(vars, fd, STDOUT_FILENO,head->infos));
}
int     check_amb(t_data *lst_words)
{
    while (lst_words && lst_words->type == space)
        lst_words = lst_words->next;
    if ((!ft_strcmp(lst_words->word, "") || space_in(lst_words->word)) && lst_words->type == word)
        return (1);
    return (0);
}
int     amb_in(t_data *lst_words)
{
    if (lst_words->type == pi_pe)
        lst_words = lst_words->next;
   while (lst_words && lst_words->type != pi_pe)
        {
            if (lst_words->type >= r_redirect && lst_words->type <= append && lst_words->type != here_doc)
                return (check_amb(lst_words->next));
            lst_words = lst_words->next;
        }
    return (0);
}
t_cmd_lines     *join_words(t_data *lst_words)
{
    t_cmd_lines *p_to_e;
    t_data *head;

    head = lst_words;
    p_to_e = NULL;

    
    while (lst_words)
    {
        if (lst_words->id == 0 || lst_words->type == pi_pe)
        {
            if (amb_in(lst_words))
               lst_words = lst_words->next;
            else 
                fill_vars(lst_words, &p_to_e);
        }
        lst_words = lst_words->next;
    }

    // int i;
    // while(p_to_e)
    // {
    //     i = 0;
    //     while (p_to_e->cmd_line[i])
    //         printf("pte : [%s]\n", p_to_e->cmd_line[i++]);
    //     printf("infile --> [%d]\n", p_to_e->infile);
    //     printf("-----------------------------------------\n");
    //     p_to_e = p_to_e->next;
    // }
    clean_list(&head);
    return (p_to_e);
}