/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/19 20:25:29 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_global	*g_global;

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
                g_global->exit_status = 1;
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

void	ft_handle_status()
{
	if(WEXITSTATUS(g_global->exit_status))
		g_global->exit_status = WEXITSTATUS(g_global->exit_status);
	else if (WIFSIGNALED(g_global->exit_status))
		g_global->exit_status = WTERMSIG(g_global->exit_status) + 128;
}

void    clean_lines2(t_cmd_lines **lines)
{
    t_cmd_lines *tmp;

    if ((*lines)->infos->n_red > 0)
        free((*lines)->infos->fds);
    while(*lines)
    {
        tmp = *lines;
        *lines = (*lines)->next;
        if (tmp->cmd_line)
            freealloc2(tmp->cmd_line);
        free(tmp);
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
    int                     fd[2];
        // glob_i = 0;
    // int i=0;
// (void)ac;
// (void)av;
// (void)env;
    // global_init();
    g_global = malloc(sizeof(t_global));
	g_global->exit_status = 0;
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
            {
                free(str);
                continue;
            }
            here_doc_func(lst_words);
            the_fucking_expand(lst_words);
            // amb(lst_words);
            //   while(lst_words)
            //     {
            //       printf("[%s]  --> [%d]\n", lst_words->word, lst_words->type);
            //      lst_words = lst_words->next;
            //     }
            //     exit(0);
            lines = join_words(lst_words);
            // printf("[%p]\n", lines->cmd_line + 6);

            if (!delete_adds(&lines) || !lines)
            {
                free(str);
                if (infos.n_red > 0)
                    free(infos.fds);
                continue;
            }
// puts("ok");
    //             int i;
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
    // if (!lines)
    // printf("addr [%p]\n", lines->infos->fds);
    // printf("[%p]\n", str);
        // clean_lines2(&lines);
        // free(str);
        // continue;
            t_cmd_lines *head;
            fd[0] = -1;
            fd[1] = -1;
            head = lines;
            int c =  builts_in(lines, &infos.env);
            // check ex_st befor execution
            if (!lines->next && (c == 1 || !c))
            {
                if (!c)
                    g_global->exit_status = 1;
                else 
                    g_global->exit_status = 0;
            }
            else
            {
                    while (lines)
                    {
                             if (!ft_execution(lines, fd))
                                break;
                            lines = lines->next;
                            ft_handle_status();
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
            // puts("ok");
            clean_lines2(&head);
        }
    }
}
}