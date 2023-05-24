/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/05/24 00:14:43 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int ac, char **av, char **env)
{
    char *str;
    t_data *lst_words;
// (void)ac;
// (void)av;
// (void)env;
if (!av[1])
{
    while(1)
    {
       str = readline(BOLD GREEN"tby_shell$ "RESET);
       if (!*str)
        free(str);
     else{
            lst_words = lexer(str);
            add_history(str);
            free(str);
            if (!lst_words)
                continue;
            clean_list(&lst_words);
        }
    }
}
    else 
        builts_in(ac, av, env);
}