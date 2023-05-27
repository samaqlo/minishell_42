/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:54:19 by astalha           #+#    #+#             */
/*   Updated: 2023/05/27 19:58:26 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     dollar_in(char *str)
{
    int i;

    i = 0;
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
               printf("var --- >[%s]\n", vars[j]);
               j++;
            }
        else
            i++;
    }
    vars[j] = NULL;
    return (vars);
}
// char    *set_value(char *var, t_list_env *env)
// {
//     while(env)
//     {
//         if (!ft_strncmp(var, "$", ft_strlen(var)))
//             return(ft_itoa(getpid()));
//         else if (!ft_strcmp(var, ft_substr(env->variable, 0, ft_strlen(env->variable) - 1)))
//         {
//             printf("env %s\n", env->variable);
//             return (env->content);
//         }
//         env = env->next;
//     }
//     return (ft_strdup(""));
// }
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
void    split_line(t_data   *cmd_line)
{
    t_expand *expands = NULL;
    char *tmp;
    int start;
    int i;
    int len;

    while(cmd_line)
    {
        i = 0;
        while(i <= (int)ft_strlen(cmd_line->word))
        {
            len = 0;
            start = i;
            len = get_len(cmd_line->word, &i);
            tmp = ft_substr(cmd_line->word, start, len);
            ft_lstadd_back_exp(&expands, ft_lstnew_exp(tmp));
            free(tmp);
        }
        cmd_line->vars = expands;
        cmd_line = cmd_line->next;
    }
    puts("ok");
}