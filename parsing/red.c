/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:33:15 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:21:44 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_lines	*del_lines(t_cmd_lines *lines)
{
	t_cmd_lines	*new;
	t_cmd_lines	*head;

	new = NULL;
	head = lines;
	while (lines)
	{
		ft_lstadd_back_exp(&new, ft_lstnew_exp(ft_strdup2(lines->cmd_line),
				lines->infile, lines->outfile, lines->infos));
		lines = lines->next;
	}
	clean_lines(&head);
	return (new);
}

int	delete_adds(t_cmd_lines **lines)
{
	char		**tmp;
	int			type;
	t_cmd_lines	*head;

	head = *lines;
	while (*lines)
	{
		type = get_type(*lines);
		if (type)
		{
			open_file(*lines);
			if ((*lines)->infile >= -1 && (*lines)->outfile >= -1)
			{
				tmp = delete_red(*lines);
				freealloc2((*lines)->cmd_line);
				(*lines)->cmd_line = tmp;
			}
		}
		*lines = (*lines)->next;
	}
	*lines = head;
	*lines = del_lines(*lines);
	if (!*lines)
		return (free(tmp), 0);
	return (1);
}
