/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:51:16 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_to_red(t_data *lst_words)
{
	lst_words = lst_words->next;
	while (lst_words)
	{
		if (lst_words->type != space)
			return (lst_words->word);
		lst_words = lst_words->next;
	}
	return (NULL);
}

void	amb(t_data *lst_words)
{
	while (lst_words)
	{
		if (lst_words->type >= r_redirect && lst_words->type <= append
			&& lst_words->type != here_doc && !is_expandable(lst_words))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(get_next_to_red(lst_words), 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			while (lst_words && lst_words->type != pi_pe)
				lst_words = lst_words->next;
		}
		else
			lst_words = lst_words->next;
	}
}

void	fill_fds(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i] = -1;
		i++;
	}
}

void	fill_list_words(t_infos *infos, char *str, t_data **lst_words)
{
	t_data	*tmp;
	char	*str1;

	init_args(infos);
	while (1)
	{
		infos->start = infos->pos;
		infos->len = word_len(str, infos);
		str1 = ft_substr_parse(str, infos);
		tmp = ft_lstnew(str1, infos);
		ft_lstadd_back(lst_words, tmp);
		if (infos->is_finish)
		{
			free(tmp);
			break ;
		}
	}
}

t_data	*lexer(char *str, t_infos *infos)
{
	t_data	*lst_words;
	int		c;

	lst_words = NULL;
	c = quoting_checker(str);
	if (c == 2 || c == 1)
		return (ft_putstr_fd("quote opened\n", 2), NULL);
	else if (c == 3)
		return (NULL);
	fill_list_words(infos, str, &lst_words);
	if (all_spaces(lst_words) || !syntaxe_checker(lst_words))
		return (clean_list(&lst_words), NULL);
	amb(lst_words);
	if (count_red(lst_words) > 0)
	{
		lst_words->infos->fds = malloc(count_red(lst_words) * sizeof(int));
		lst_words->infos->n_red = count_red(lst_words);
		fill_fds(lst_words->infos->fds, lst_words->infos->n_red);
	}
	return (lst_words);
}
