/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:31 by astalha           #+#    #+#             */
/*   Updated: 2023/04/30 17:46:42 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
#define MINISHEL_H

#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/readline.h>

typedef struct s_infos
{
    int     n_pipes;
}               t_infos;

typedef struct s_data
{
    char    *word;
    char    type;
    t_infos *infos;
    enum words_types{word, r_redirect, l_redirect, here_doc, append, pi_pe};
    
    struct  s_data *next;
}              t_data;

int quoting_checker(char *str, t_infos *infos);

#endif

