/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/14 03:39:11 by astalha          ###   ########.fr       */
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
void    sig_handl(int sig)
{
        if (sig == SIGINT && waitpid(-1, NULL, WNOHANG))
        {
                ft_putstr_fd("\n", 1);
                rl_replace_line("", 0);
                rl_on_new_line();
                rl_redisplay();
        }
        else if (sig == SIGQUIT)
                return ;
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
        int                     fd[2];
    // int i=0;
// (void)ac;
// (void)av;
// (void)env;
    grep_env(env, &infos.env);
if (!av[1])
{
    while(1)
    {
         signal(SIGINT, &sig_handl);
        signal(SIGQUIT, &sig_handl);
        rl_catch_signals = 0;
       str = readline(BOLD GREEN"tby_shell$ "RESET);
       if (str && !*str)
            free(str);
        else if (!str)
        {
            ft_putstr_fd("exit\n", 1);
            free(str);
            exit(0);
        }
     else{
            add_history(str);
            lst_words = lexer(str, &infos);
            if (!lst_words)
                continue;
            here_doc_func(lst_words);
            // while(1);
            the_fucking_expand(lst_words);
            // amb(lst_words);
            //   while(lst_words)
            //     {
            //       printf("[%s]  --> [%d]\n", lst_words->word, lst_words->type);
            //      lst_words = lst_words->next;
            //     }
            //     exit(0);
            lines = join_words(lst_words);
            if (!delete_adds(&lines))
                continue;
                int i;
    // while(lines)
    // {
    //     i = 0;
    //     while (lines->cmd_line[i])
    //         printf("pte : [%s]\n", lines->cmd_line[i++]);
    //     printf("infile --> [%d]\n", lines->infile);
    //     printf("oufile --> [%d]\n", lines->outfile);
    //     printf("-----------------------------------------\n");
    //     lines = lines->next;
    // }
    // exit(0);
    if (!lines)
        continue;
            fd[0] = -1;
            fd[1] = -1;
            if (!lines->next && builts_in(lines, &infos.env))
                    ;
            else
            {
                    while (lines)
                    {
                            ft_execution(lines, fd);
                            lines = lines->next;
                    }
            }
            while (wait(0) != -1)
                    ;
            close(fd[0]);
            // free(str);
            // if(lines->cmd_line[1])
            //  printf("%c\n", lines->cmd_line[1][0]);
            // puts("ok");
            // builts_in(lines, &infos.env);
            // print_list(lst_words);
            free(str);
            // clean_list(&lst_words);
        }
    }
}
    exit(100);
}