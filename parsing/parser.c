/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:28:17 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:21:38 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_vars(t_data *lst_words, t_cmd_lines **p_to_e)
{
	char	**vars;
	t_data	*head;
	int		id;
	int		fd;
	int		i;

	initvr(&head, &i, &fd, lst_words);
	vars = (char **)malloc((count_w(lst_words) + 1) * sizeof(char *));
	if (lst_words->type == pi_pe)
		lst_words = lst_words->next;
	while (lst_words && lst_words->type != pi_pe)
	{
		if (lst_words->type != space)
		{
			id = fill_vars3(&lst_words, &i, vars, &fd);
			if (!id)
				break ;
			else if (id == 1)
				continue ;
		}
		lst_words = lst_words->next;
	}
	vars[i] = NULL;
	ft_lstadd_back_exp(p_to_e, ft_lstnew_exp(vars, fd, STDOUT_FILENO,
			head->infos));
}

int	check_amb(t_data *lst_words)
{
	while (lst_words && lst_words->type == space)
		lst_words = lst_words->next;
	if (lst_words->next && lst_words->next->type != space)
		return (0);
	if ((!ft_strcmp(lst_words->word, "") || (space_in(lst_words->word)
				&& lst_words->word[ft_strlen(lst_words->word) - 1] != ' '))
		&& lst_words->type == word)
		return (1);
	return (0);
}

int	amb_in(t_data *lst_words)
{
	if (lst_words->type == pi_pe)
		lst_words = lst_words->next;
	while (lst_words && lst_words->type != pi_pe)
	{
		if (lst_words->type >= r_redirect && lst_words->type <= append
			&& lst_words->type != here_doc)
			return (check_amb(lst_words->next));
		lst_words = lst_words->next;
	}
	return (0);
}

t_cmd_lines	*join_words(t_data *lst_words)
{
	t_cmd_lines	*p_to_e;
	t_data		*head;

	head = lst_words;
	p_to_e = NULL;
	while (head)
	{
		if (head->id == 0 || head->type == pi_pe)
		{
			if (amb_in(head))
				g_global->exit_status = 1;
			fill_vars(head, &p_to_e);
		}
		head = head->next;
	}
	clean_list(&lst_words);
	return (p_to_e);
}
