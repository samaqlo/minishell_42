/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:44 by astalha           #+#    #+#             */
/*   Updated: 2023/06/12 18:34:55 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void   sig_handl(int sig)
{
    if(sig == SIGINT && waitpid(-1, NULL, WNOHANG))
    {
        ft_putstr_fd("\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if(sig == SIGQUIT)
        return ;
}

int     is_redrect(char *str)
{
    if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<") || !ft_strcmp(str, ">>"))
        return (1);
    return (0);
}

int     main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int fd[2];

    fd[0] = -1;
    fd[1] = -1;
	t_list_env	*enev;
    char *str;
    t_data *lst_words;
    t_cmd_lines *lines;
    t_infos infos;
    infos.env = NULL;
	enev = NULL;
    grep_env(env, &infos.env);
    if (!av[1])
    {
        while(1)
        {
            signal(SIGINT, &sig_handl);
            signal(SIGQUIT, &sig_handl);
            rl_catch_signals = 0;
            str = readline(BOLD GREEN"tby_shell$ "RESET);
            if(str && !*str)
                free(str);
            else if (!str)
            {
                ft_putstr_fd("exit\n", 1);
                free(str);
                exit(0);
            }
            else
            {
                add_history(str);
                lst_words = lexer(str, &infos);

                if (!lst_words)
                    continue ;
                here_doc_func(lst_words);
                the_fucking_expand(lst_words);
                lines = join_words(lst_words);
                delete_adds(lines);
                fd[0] = -1;
                fd[1] = -1;
                while(lines)
                {
                    // ft_execution(lines, fd);
                    if (builts_in(lines, &infos.env) != 1)
                        ft_execution(lines, fd);
                    lines = lines->next;
                }
                while (wait(0)!= -1 || errno != ECHILD)
                    ;
                close(fd[0]);
                free(str);
                clean_list(&lst_words);
            }
        }
    }
    exit(100);
}
