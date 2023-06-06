/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/06 04:32:10 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_list(t_data *lst_words)
{
    int i;
     while(lst_words)
    {
        i = 0;
        printf("word : [%s] || type : [%d]\n", lst_words->word, lst_words->type);
        lst_words= lst_words->next;
    }
}
int     main(int ac, char **av, char **env)
{
    char *str;
    t_data *lst_words;
    t_infos infos;
    // int i=0;
// (void)ac;
// (void)av;
// (void)env;
    grep_env(env, &infos.env);
if (!av[1])
{
    while(1)
    {
       str = readline(BOLD GREEN"tby_shell$ "RESET);
       if (!*str)
        free(str);
     else{
            add_history(str);
            lst_words = lexer(str, &infos);
            if (!lst_words)
                continue;
            here_doc_func(lst_words);
            the_fucking_expand(lst_words);
            join_words(lst_words);
            // print_list(lst_words);
            free(str);
            clean_list(&lst_words);
        }
    }
}
    else 
        builts_in(ac, av, env);

    exit(100);
}