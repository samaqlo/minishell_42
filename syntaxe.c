/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:53:34 by astalha           #+#    #+#             */
/*   Updated: 2023/05/21 23:26:45 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_next_type(t_data *cmd_line)
{
    while(cmd_line->type == space)
        cmd_line = cmd_line->next;
    return (cmd_line->type);
}
int     syntaxe_checker(t_data  *cmd_line)
{
    if (!cmd_line)
        return (0);
    while(cmd_line->next)
    {
        if ((cmd_line->type >= r_redirect && cmd_line->type <= append) && (get_next_type(cmd_line->next) >= r_redirect && get_next_type(cmd_line->next) <= pi_pe))
        {
            printf("minishell: syntax error near unexpected token");
            if (get_next_type(cmd_line->next) == r_redirect)
                puts("`>\'");
            else if (get_next_type(cmd_line->next) == l_redirect)
                puts("`<\'");
            else if (get_next_type(cmd_line->next) == append)
                puts("`>>\'");
            else if (get_next_type(cmd_line->next) == here_doc)
                puts("`<<\'");
            else if (get_next_type(cmd_line->next) == l_redirect)
                puts("`<\'");
            else if (get_next_type(cmd_line->next) == pi_pe)
                puts("`|\'");
            return (0);
        }
        cmd_line = cmd_line->next;
    }
    return (1);
}