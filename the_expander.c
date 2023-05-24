/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:54:19 by astalha           #+#    #+#             */
/*   Updated: 2023/05/24 02:12:28 by astalha          ###   ########.fr       */
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
void    get_the_dollar(t_data   *cmd_line)
{
    
}
char     *find_vr(char    *str, char **envp)
{
    t_list_env  *env;

    grep_env(envp, env);
}