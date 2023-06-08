/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/08 20:48:11 by ohaimad          ###   ########.fr       */
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
	t_list_env	*enev;
	enev = NULL;
    char *str;
    (void)ac;
    (void)av;
    t_data *lst_words;
    t_cmd_lines *lines;
    t_infos infos;
    infos.env = NULL;
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
            lines = join_words(lst_words);
            delete_adds(lines);
            // if(lines->cmd_line[1])
            //  printf("%c\n", lines->cmd_line[1][0]);
            builts_in(lines, &infos.env);
            // print_list(lst_words);
            free(str);
            clean_list(&lst_words);
        }
    }
}
    exit(100);
}