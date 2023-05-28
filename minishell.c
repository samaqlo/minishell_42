/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/05/28 06:37:00 by astalha          ###   ########.fr       */
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
        printf("vars --------------------------------------------------\n");
        while(lst_words->vars[i])
        {
            printf("vars --> [%s]\n", lst_words->vars[i]);
            i++;
        }
        printf("end vars--------------------------------------------------\n");

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
            lst_words = lexer(str, &infos);
            // get_the_dollar(lst_words);
            the_fucking_expand(lst_words);
            // print_list(lst_words);
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