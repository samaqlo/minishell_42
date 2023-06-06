/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/06/06 13:33:23 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BOLD "\033[1m"
# define RESET "\033[0m"

 enum words_types{
    word,
    sq_word,
    dq_word,
    r_redirect,
    l_redirect,
    here_doc, 
    append,
    pi_pe,
    space};

typedef struct s_cmd_lines
{
    char **cmd_line;
    int infile;
    int outfile;
    struct s_cmd_lines *next;
}               t_cmd_lines;

typedef struct s_list_env
{
    char *variable;
    char *content;
    int     c;
    struct s_list_env *next;
}               t_list_env;

typedef struct s_infos
{
    int     n_pipes;
    int     is_quote;
    int     flag;
    int     pos;
    int     start;
    int     len;
    int     is_finish;
    t_list_env  *env;
}               t_infos;

typedef struct s_data
{
    char    *word;
    int      tfree;
    int     id;
    int    type;
    char    **vars;
    t_infos *infos;
    int     fd_here_doc;
    struct  s_data *next;
}              t_data;


int quoting_checker(char *str);
t_data    *lexer(char *str, t_infos *infos);
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
// void    get_the_dollar(t_data   *cmd_line);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strrchr_env(const char *s, int c);
int	builts_in(int ac, char **av, char **env);
void    print_error(int code, int type);
void	grep_env(char **env, t_list_env **enev);

t_cmd_lines	*ft_lstnew_exp(char **content, int fd);
void	ft_lstadd_back_exp(t_cmd_lines **lst, t_cmd_lines *new);
void    split_line(t_data   *cmd_line);
t_cmd_lines	*ft_lstlast_exp(t_cmd_lines *lst);
void    the_fucking_expand(t_data *lst_words);
void    here_doc_func(t_data *lst_words);
int     dollar_in(char *str);
int     get_len(char *str, int *i);
int     len_of_word(char *str, int *i);
int     dollar_len(char *str, int *i);
int     white_sp_len(char *str, int *i);
char    *set_value(char *var, t_list_env *env);
void    print_list(t_data *lst_words);
int     count_words(char *str);
char     *expand_in_hd(char *str, t_list_env *env);
char    *two_to_one(char **vars);
void	freealloc2(char **ptr);
void    set_ids(t_data *lst_words);
t_cmd_lines     *join_words(t_data *lst_words);
void    open_err(char *file_name, int code);
void    delete_adds(t_cmd_lines *lines);
#endif

