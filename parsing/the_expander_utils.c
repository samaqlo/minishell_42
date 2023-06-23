/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:56:07 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:48:09 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_prev(t_data *lst_words, int id)
{
	while (lst_words->id != id)
	{
		if (lst_words->type == here_doc && check_next_2hd(lst_words->next, id))
			return (1);
		lst_words = lst_words->next;
	}
	return (0);
}

int	check_next_2hd(t_data *lst_words, int id)
{
	if (lst_words->type == space)
		lst_words = lst_words->next;
	while (lst_words->id <= id)
	{
		if (lst_words->type == space)
			return (0);
		else if (lst_words->id == id)
			return (1);
		lst_words = lst_words->next;
	}
	return (0);
}

void	set_ids(t_data *lst_words)
{
	int	i;

	i = 0;
	while (lst_words)
	{
		lst_words->id = i;
		i++;
		lst_words = lst_words->next;
	}
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(" \t\n\v\f\r", str[i]))
		{
			count++;
			white_sp_len(str, &i);
		}
		else if (ft_strchr("$", str[i]))
		{
			count++;
			dollar_len(str, &i);
		}
		else
		{
			count++;
			len_of_word(str, &i);
		}
	}
	return (count);
}

int	get_len(char *str, int *i)
{
	if (str[*i] == '$' && (ft_isdigit(str[*i + 1]) || str[*i + 1] == '?'))
		return ((*i) += 2, 2);
	while (str[*i])
	{
		if (ft_strchr(" \t\n\v\f\r", str[*i]))
			return (white_sp_len(str, i));
		else if (ft_strchr("$", str[*i]))
			return (dollar_len(str, i));
		else
			return (len_of_word(str, i));
		(*i)++;
	}
	return (0);
}
