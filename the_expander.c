/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:54:19 by astalha           #+#    #+#             */
/*   Updated: 2023/06/17 21:51:19 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int     space_in(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[i]))
            return (1);
        i++;
    }
    return (0);
}
int     dollar_in(char *str)
{
    int i;

    i = 0;
    if (ft_strlen(str) < 1)
        return (0);
    while(str[i])
    {
        if (str[i] == '$')  
            return (1);
        i++;
    }
    return (0);
}

char    *get_var(char *str, int *i)
{
    int oi;

    oi = *i;
    if (str[*i] == '$')
        return ((*i)++, ft_substr(str, *i - 1, 1));
    while(str[*i])
    {
        if (!str[*i + 1])
           return ((*i)++, ft_substr(str, oi, *i - oi));
        else if ((!ft_isalnum(str[*i]) && str[*i] != '_'))
            return (ft_substr(str, oi, *i - oi));
        (*i)++;
    }
    return (NULL);
}

int count_dlr(char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(str[i])
    {
        if (str[i] == '$' && str[i - 1] != '$')
            len++;
        i++;
    }
    return len;
}
char   **find_vr(t_data *cmd_line)
{
    int i;      
    int j;
    char **vars;
    i = 0;
    j = 0;
    vars = (char **)malloc((count_dlr(cmd_line->word) + 1) * sizeof(char *));
    while(cmd_line->word[i])
    {
        if (cmd_line->word[i] == '$')
            {
               i++;
               vars[j] = get_var(cmd_line->word, &i);
               j++;
            }
        else
            i++;
    }
    vars[j] = NULL;
    return (vars);
}

char  *skip_space(char *str)
{
    int i;
    int j;
    i = 0;
    j = 0;
    if (!space_in(str))
        return (str);
    while(str[i])
    {
        while (ft_strchr(" \t\n\v\f\r", str[i]))
            i++;
        i++;
        j++;
    }
    j++;
    char *tmp = malloc(j);
    i = 0;
    j = 0;
    while(str[i])
    {
        if ((ft_strchr(" \t\n\v\f\r", str[i]) && (!ft_strchr(" \t\n\v\f\r", str[i + 1]) || !str[i + 1])) || !ft_strchr(" \t\n\v\f\r", str[i]))
        {
            tmp[j] = str[i];
             i++;
            j++;
            }
        else if (ft_strchr(" \t\n\v\f\r", str[i]))
            i++;
    }
    return tmp;
}
char    *set_value(char *var, t_list_env *env)
{
    char *tmp;
    char *str;
    // printf("[%s]\n", var);
    // if (ft_strlen(var) == 1)
    //     return (ft_strdup(var));
    tmp = ft_strdup(var + 1);
    if (!ft_strcmp(tmp, "?"))
    {
        free(tmp);
        tmp = ft_itoa(g_global->exit_status);
        return (tmp);
    }
    while(env)
    {
        str = ft_substr(env->variable, 0, ft_strlen(env->variable));
        if (!ft_strncmp(tmp, "$", ft_strlen(tmp)))
            return(free(str), free(tmp), ft_strdup(""));
        else if (!ft_strcmp(tmp, str))
            return (free(str), free(tmp), ft_strdup(env->content));
        env = env->next;
        free(str);
    }
    return (free(tmp), ft_strdup(""));
}
// char    **replace_vars(t_data *cmd_line)
// {
//     char **exp;
//     int i;

//     i = 0;
//     printf("ndlrs : %d\n", count_dlr(cmd_line->word));
//     exp = (char **)malloc((count_dlr(cmd_line->word) + 1) * sizeof(char *));
//     while (cmd_line)
//     {
//         i = 0;
//         if (cmd_line->dollars)
//             {
//                 while (cmd_line->dollars[i])
//                 {
//                     exp[i] = set_value(cmd_line->dollars[i], cmd_line->infos->env);
//                      printf("var --- >[%s]\n", exp[i]);
//                     i++;
//                 }
//             }
//         cmd_line = cmd_line->next;
//     }
//     return (exp);
// }
// void    get_the_dollar(t_data   *cmd_line)
// {
//     t_data *head;
//     head = cmd_line;
//     while(cmd_line)
//     {
//         if (dollar_in(cmd_line->word) && (cmd_line->type == word || cmd_line->type == dq_word))
//         {
//             cmd_line->dollars = find_vr(cmd_line);
//             // printf("cmd dllrs %s\n", cmd_line->dollars[4]);
//             // cmd_line->expands = replace_vars(cmd_line);
//         }
//         else 
//         {
//             cmd_line->dollars = NULL;
//             cmd_line->expands = NULL;
//         }
//         cmd_line = cmd_line->next;
//     }
    
//         puts("ok1");
//     int i = 0;
//     while(head)
//     {
//      i = 0;
//      if (head->dollars)
//      {
//         while(head->dollars[i])
//         {
//             printf("%s\n", head->dollars[i]);
//             // printf("%s\n", head->expands[i]);
//             i++;
//         }
//      }   
//      head = head->next;
//     }    
// }

int white_sp_len(char *str, int *i)
{
    int len = 0;
    
    while(str[*i])
    {
        if (!ft_strchr(" \t\n\v\f\r", str[*i]))
            break;
        len++;
        (*i)++;
    }
    return (len);
}
int     dollar_len(char *str, int *i)
{           
    int len = 0;
    len++;
    (*i)++;
    while(str[*i])
    {
        if (str[*i - 1] == '$' && ft_isdigit(str[*i]))
            return ((*i)++, 2);
        if (str[*i - 1] == '$' && str[*i] == '$')
            return ((*i)++, 2);
        else if (!ft_isalnum(str[*i]) && str[*i] != '_')
            break;
        (*i)++;
        len++;
    }
    return len;
}
int     len_of_word(char *str, int *i)
{
    int len = 0;
    while(str[*i])
        {
            if (ft_strchr(" \t\n\v\f\r$", str[*i]))
                return (len);
            (*i)++;
            len++;
        }
    return (len);
}
int     get_len(char *str, int *i)
{
    if (str[*i] == '$' && (ft_isdigit(str[*i + 1]) || str[*i + 1] == '?'))
        return ((*i) += 2, 2);
    while (str[*i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[*i]))
            return (white_sp_len(str, i));
        else if(ft_strchr("$", str[*i]))
            return (dollar_len(str, i));
        else
            return (len_of_word(str, i));
        (*i)++;
    }
    return (0);
}
int     count_words(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[i]))
        {
            count++;
            white_sp_len(str, &i);
        }
        else if(ft_strchr("$", str[i]))
        {
            count++;
            dollar_len(str, &i);
        }
        else
        {
            count++;
            len_of_word(str, &i);
        }
    }
    return (count);
}
void    set_ids(t_data *lst_words)
{
    int i;

    i = 0;
    while(lst_words)
    {
        lst_words->id = i;
        i++;
        lst_words = lst_words->next;
    }
}
int     check_next_2hd(t_data *lst_words, int id)
{
    if (lst_words->type == space)
        lst_words = lst_words->next;
    while(lst_words->id <= id)
    {
        if (lst_words->type == space)
            return (0);
        else if (lst_words->id == id)
            return (1);
        lst_words = lst_words->next;
    }   
    return (0);
}
int     check_prev(t_data   *lst_words, int id)
{
    while (lst_words->id != id)
    {
        if (lst_words->type == here_doc && check_next_2hd(lst_words->next, id))
            return (1);
        lst_words = lst_words->next;
    }
    return (0);
}
void    split_line(t_data   *cmd_line)
{
    char *tmp;
    int start;
    int i;
    int j = 0;
    int len;
    t_data *head;
    head = cmd_line;
    while(cmd_line)
    {
        i = 0;
        j = 0;
        cmd_line->vars = (char **)malloc((count_words(cmd_line->word) + 1) * sizeof(char *));
        while(cmd_line->word[i])
        {
            len = 0; 
            start = i;
            len = get_len(cmd_line->word, &i);
            tmp = ft_substr(cmd_line->word, start, len);
            if (!ft_strcmp(tmp, "$"))
            {
                if ((cmd_line->next && cmd_line->next->type == space) || !cmd_line->next)
                     cmd_line->vars[j] = ft_strdup(tmp);
                else
                  cmd_line->vars[j] = set_value(tmp, cmd_line->infos->env);
            }
            else if (dollar_in(tmp) && (cmd_line->type == word || cmd_line->type == dq_word) && !check_prev(head, cmd_line->id))
            {
                cmd_line->exp = 1;
                if (cmd_line->type == word)
                    cmd_line->vars[j] = skip_space(set_value(tmp, cmd_line->infos->env));
                else
                    cmd_line->vars[j] = set_value(tmp, cmd_line->infos->env);
            }
            else
                cmd_line->vars[j] = ft_strdup(tmp);
            j++;
            free(tmp);
        }
        cmd_line->vars[j] = NULL;
        cmd_line = cmd_line->next;
    }
}

char    *two_to_one(char **vars)
{
    int i;
    char *line = ft_strdup("");
    char *tmp ;
    i = 0;
    while(vars[i])
    {
        tmp = ft_strjoin(line, vars[i]);
        free(line);
        line = tmp;
        free(vars[i]);
        i++;
    }
    free(vars);
    return (line);
}

void    the_fucking_expand(t_data *lst_words)
{
        split_line(lst_words);
        while (lst_words)
        {
            free(lst_words->word);
            lst_words->word = two_to_one(lst_words->vars);
            lst_words = lst_words->next;
        }
}