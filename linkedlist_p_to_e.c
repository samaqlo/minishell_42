/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_p_to_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:04:14 by astalha           #+#    #+#             */
/*   Updated: 2023/06/11 14:39:09 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_exp(t_cmd_lines **lst, t_cmd_lines *new)
{
	t_cmd_lines	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
	lastlst = ft_lstlast_exp(*lst);
	lastlst->next = new;
}

void	ft_lstadd_front_exp(t_cmd_lines **lst, t_cmd_lines *new)
{	
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize_exp(t_cmd_lines *lst)
{
	int		i;
	t_cmd_lines	*plst;

	i = 0;
	if (!lst)
		return (0);
	plst = lst;
	while (plst != NULL)
	{
		plst = plst->next;
		i++;
	}
	return (i);
}

t_cmd_lines	*ft_lstlast_exp(t_cmd_lines *lst)
{
	t_cmd_lines	*plst;

	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

// static int	word_count(char **content)
// {
// 	int	i;

// 	i = 0;
// 	while (content[i])
// 		i++;
// 	return (i);
// }

// static int	fill_cmd_line(char **cmd_line, char **content)
// {
// 	int	i;

// 	i = 0;
// 	while (content[i])
// 	{
// 		cmd_line[i] = ft_strdup(content[i]);
// 		i++;
// 	}
// 	cmd_line[i] = NULL;
// 	return (i);
// }

t_cmd_lines	*ft_lstnew_exp(char **content, int fd, t_infos *infos)
{
	t_cmd_lines	*new;

	new = (t_cmd_lines *) malloc (sizeof (t_cmd_lines));
	if (!new)
		return (NULL);
	// fill_cmd_line(new->cmd_line, content);
	new->cmd_line = content;
	new->infile = fd;
	new->outfile = STDOUT_FILENO; 
	new->infos = infos;
	new->next = NULL;
	return (new);
}
