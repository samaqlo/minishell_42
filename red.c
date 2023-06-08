/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:33:15 by astalha           #+#    #+#             */
/*   Updated: 2023/06/08 18:48:51 by astalha          ###   ########.fr       */
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
void    set_fd(int **fds, int fd)
{
    int i = 0;
    while(*fds[i] != 0)
        i++;
    *fds[i] = fd;
}
int     priority(char **vars, int i)
{
    int flag;

    flag = 0;
        printf("pr[%s]\n", vars[i]);
    while (vars[i])
    {
        if (!ft_strcmp(vars[i], "<<"))
            flag = 0;
        else if (!ft_strcmp(vars[i], "<"))
            flag = 1;
        i++;
    }
    return (flag);
}
void     open_file(t_cmd_lines *lines, int type)
{
    int i = 0;
    int fd;
    while(lines->cmd_line[i])
    {
        if (is_red(lines->cmd_line[i]))
            {
                if (!ft_strcmp(lines->cmd_line[i], "<"))
                {
                    fd = open(lines->cmd_line[i + 1], O_RDONLY, 0444);
                    if (priority(lines->cmd_line, i))
                        lines->infile = fd;
                    lines->infos->fds[lines->infos->index++] = fd;
                    if (lines->infile < 0)
                        open_err(lines->cmd_line[i + 1], 0);
                }
                else if (type == r_redirect)
                {
                    lines->outfile = open(lines->cmd_line[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
                    lines->infos->fds[lines->infos->index++] = lines->outfile;
                    if (lines->outfile < 0)
                        open_err(lines->cmd_line[i + 1], 1);
                }
                else if (type == append)
                {
                    lines->outfile = open(lines->cmd_line[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
                    lines->infos->fds[lines->infos->index++] = lines->outfile;             
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
int     space_in2(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[i]) && !is_red(str))
            return (1);
        i++;
    }
    return (0);
}
int     vars_len(char  **vars)
{
    int i;

    i = 0;
    while(vars[i])
        i++;
    i += 2;
    return (i);
}
char   **minisplit(char **vars)
{
    int i;
    int len;
    int start;
    char **ret;
    char *tmp;
    int j;

    i = 0;
    j = 0;
    ret = malloc(vars_len(vars) * sizeof(char *));
    tmp = vars[i];
    while(ft_strchr(" \t\n\v\f\r", tmp[i]))
        i++;
    while(tmp[i])
    {
        start = i;
        if (j)
            break;
        len = get_len(tmp, &i);
        if (!j)
            {
                ret[j] = ft_substr(tmp, start, len);
                (j)++;
            }
    }
    ret[j] = ft_substr(tmp, start, ft_strlen(tmp + start));
    j++;
    i = 1;
    while(vars[i])
    {
        ret[j] = ft_strdup(vars[i]);
        i++;
        j++;
    }
    ret[j] = NULL;
    i = 0;
    while(ret[i])
        printf("ret [%s]\n", ret[i++]);
    freealloc2(vars);
    return(ret);
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
         else if (lines->cmd_line[i])
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
        if (space_in2(lines->cmd_line[0]))
            {
                tmp = minisplit(lines->cmd_line);
                lines->cmd_line = tmp;
            }
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
    i = 0;
    lines = head;

    while(i < lines->infos->n_red)
    {
        printf("file %d = [%d]\n", i+1, lines->infos->fds[i]);
        i++;
    }
}
