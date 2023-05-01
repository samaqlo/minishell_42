/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/04/30 16:55:31 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"


int     main(int ac, char **av, char **env)
{
    char *str;
    t_infos infos;
    while(1)
    {
       str = readline("minishel> ");
        printf("%s\n",str);
        if (quoting_checker(str, &infos))
            return (perror("opened quotes\n"), 0);
        
        free(str);
    }
}