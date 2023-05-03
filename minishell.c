/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/05/02 11:25:46 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int     main(int ac, char **av, char **env)
{
    char *str;
(void)ac;
(void)av;
(void)env;
    while(1)
    {
       str = readline("minishel> ");
        if (quoting_checker(str))
            return (perror("opened quotes\n"), 0);
        lexer(str);
        free(str);
    }
}