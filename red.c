/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:33:15 by astalha           #+#    #+#             */
/*   Updated: 2023/06/07 10:42:36 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_type(t_cmd_lines *line)
{
    int i = 0;

    while (line->cmd_line[i])
    {
        if (!ft_strcmp(">", line->cmd_line[i]))
            return (r_redirect);
        else if (!ft_strcmp("<", line->cmd_line[i]))
            return (l_redirect);
        else if (!ft_strcmp(">>", line->cmd_line[i]))
            return (append);
        else if (!ft_strcmp("<<", line->cmd_line[i]))
            return (here_doc);
        i++;
    }
    return (0);
}
int     is_red(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (ft_strchr("<>", str[i]))
            return (1);
        i++;
    }
    return (0);
}
void     open_file(t_cmd_lines *lines, int type)
{
    int i = 0;
    while(lines->cmd_line[i])
    {
        if (is_red(lines->cmd_line[i]))
            {
                if (type == l_redirect && !ft_strcmp(lines->cmd_line[i], "<"))
                {
                    lines->infile = open(lines->cmd_line[i + 1], O_RDONLY, 0444);
                    if (lines->infile < 0)
                        open_err(lines->cmd_line[i + 1], 0);
                }
                else if (type == r_redirect)
                {
                    lines->outfile = open(lines->cmd_line[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
                    if (lines->outfile < 0)
                        open_err(lines->cmd_line[i + 1], 1);
                }
                else if (type == append)
                {
                    lines->outfile = open(lines->cmd_line[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
                    if (lines->outfile < 0)
                        open_err(lines->cmd_line[i + 1], 1);
                }
            }
        i++;
    }
}
int     get_new_lenght(char **vars)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while(vars[i])
    {
        if (is_red(vars[i]))
            i += 2;
        len++;
        if(vars[i])
            i++;
    }
    return (len);
}
char    **delete_red(t_cmd_lines *lines)
{
    char **tmp;
    int i;
    int j;

    j = 0;
    i = 0;
    tmp = malloc((get_new_lenght(lines->cmd_line) + 1) * sizeof(char *));

    while(lines->cmd_line[i])
    {
        if (is_red(lines->cmd_line[i]))
            i += 2;
        if (lines->cmd_line[i])
        {
            tmp[j] = ft_strdup(lines->cmd_line[i]);
            j++;
            i++;
        }
    }
    tmp[j] = NULL;
    return (tmp);
}
void    delete_adds(t_cmd_lines *lines)
{
    char **tmp;
    int type;

    type = 0;
    t_cmd_lines *head;
    head = lines;
    while(lines)
    {
        type = get_type(lines);
        if (type)
        {
            open_file(lines, type);
            tmp = delete_red(lines);
            freealloc2(lines->cmd_line);
            lines->cmd_line = tmp;
        }
        lines = lines->next;
    }
    lines = head;
    int i =0;
    while(lines)
    {
        i = 0;
        while(lines->cmd_line[i])
            printf("word : [%s]\n", lines->cmd_line[i++]);
        printf("infile --> [%d]\n", lines->infile);
        printf("oufile --> [%d]\n", lines->outfile);
        printf("------------------------------------------\n");
        lines = lines->next;
    }
}