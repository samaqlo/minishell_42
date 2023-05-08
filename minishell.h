/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/05/08 12:37:04 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/readline.h>
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
    pi_pe};
    
typedef struct s_infos
{
    int     n_pipes;
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
    struct s_list_env *next;
} t_list_env;


int quoting_checker(char *str);
void    lexer(char *str);
//linked_list
void	ft_lstadd_back(t_data **lst, t_data *new);
void	ft_lstadd_front(t_data **lst, t_data *new);
int	ft_lstsize(t_data *lst);
t_data	*ft_lstlast(t_data *lst);
t_data	*ft_lstnew(char *content);

#endif

