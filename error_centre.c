/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_centre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:53:34 by astalha           #+#    #+#             */
/*   Updated: 2023/05/24 00:12:26 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_code_0(int type)
{
    char *spchar = NULL;

    if (type == r_redirect)
        spchar = ft_strdup(">");
    else if (type == l_redirect)
        spchar = ft_strdup("<");
    else if (type == here_doc)
        spchar = ft_strdup("<<");   
    else if (type == append)
        spchar = ft_strdup(">>"); 
    else if (type == pi_pe)
        spchar = ft_strdup("|");
    ft_putstr_fd_edit("minishell: syntax error near unexpected token `", spchar, 2);
}
void    print_error(int code, int type)
{
    if (!code && type)
        print_code_0(type);
    else if (code == 1 && !type)
        ft_putstr_fd("minishell: syntax error near unexpected token `newline\'\n", 2);
    else if (code == 2 && !type)
        ft_putstr_fd("minishell: unexpected input\n", 2);
}
int     check_for_errors(int    *types, int len)
{
    int i;
    int j;

    i = 0;
    j = 1;
    if (types[i] == pi_pe)
        return (print_error(1, 0), free(types), 0);
    while(j <= len)
        {
            if ((types[i] >= r_redirect) && j == len)
                return (print_error(1, 0), free(types), 0);
            else if (((types[i] >= r_redirect && types[i] <= append) && types[j] >= r_redirect) || (types[i] == pi_pe && types[j] == pi_pe))
                    return (print_error(0, types[j]), free(types), 0);
            else if (types[i] == pi_pe && (types[j] >= r_redirect && types[j] <= append) && types[j + 1] && (types[j + 1] >= r_redirect))
            {
                if (types[j + 1] && (types[j + 1] >= r_redirect))
                    return (print_error(0, types[j + 1]), free(types), 0);
                return (print_error(1, 0), free(types), 0);
            }
            i++;
            j++;
        }
        i--;
    if (types[i] >= r_redirect && types[i] != space)
        return (print_error(1, 0), free(types), 0);
    free(types);
    return (1);
}
int     syntaxe_checker(t_data  *cmd_line)
{
    int i;
    int len;
    int *types;

    i = 0;
    len = ft_lstsize(cmd_line);
    types = malloc(len * sizeof(int));
    while(cmd_line)
    {
        if (cmd_line->type != space)
        {
            types[i] = cmd_line->type;
            cmd_line = cmd_line->next;
            i++;
        }
        else
            cmd_line = cmd_line->next;
    }
    if (!check_for_errors(types, len))
        return (0);
    return (1);
} 