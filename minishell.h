/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/05/21 21:44:06 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/readline.h>

 enum words_types{
    word,
    sq_word,
    dq_word,
    r_redirect,
    l_redirect,
    here_doc, 
    append,
    pi_pe,
    dollar,
    space};

typedef struct s_infos
{
    int     n_pipes;
    int     is_quote;
    int     flag;
    int     pos;
    int     start;
    int     len;
    int     is_finish;
}               t_infos;

typedef struct s_data
{
    char    *word;
    int    type;
    t_infos *infos;
    struct  s_data *next;
}              t_data;

typedef struct s_list_env
{
    char *variable;
    char *content;
    int     c;
    struct s_list_env *next;
}               t_list_env;

int quoting_checker(char *str);
int    lexer(char *str);
char	*ft_substr_parse(char const *s, t_infos	*infos);
//linked_list
void	ft_lstadd_back(t_data **lst, t_data *new);
void	ft_lstadd_front(t_data **lst, t_data *new);
int	ft_lstsize(t_data *lst);
t_data	*ft_lstlast(t_data *lst);
t_data	*ft_lstnew(char *content, t_infos	*infos);
//cleaners
void     clean_list(t_data   **lst_words);


int     syntaxe_checker(t_data  *cmd_line);
int     strat_end_checker(char *str);
#endif

