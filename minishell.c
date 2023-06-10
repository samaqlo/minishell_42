/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/09 22:56:33 by astalha          ###   ########.fr       */
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

// void    init_help(t_help *help, t_data *lst_words)
// {
//     help->n_red = count_red(lst_words);
//     help->fds = calloc(help->n_red , sizeof(int));
//     help->index = 0;
// }
int     is_redrect(char *str)
{
    if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>"))
        return (1);
    return (0);
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
            // while(1);
            the_fucking_expand(lst_words);
            // amb(lst_words);
            lines = join_words(lst_words);
            delete_adds(lines);
            // if(lines->cmd_line[1])
            //  printf("%c\n", lines->cmd_line[1][0]);
            // puts("ok");
            builts_in(lines, &infos.env);
            // print_list(lst_words);
            free(str);
            clean_list(&lst_words);
        }
    }
}
    exit(100);
}