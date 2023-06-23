/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:37:47 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:19:16 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	conditions(t_infos *infos, char *str, int *i, int *len)
{
	if (!infos->is_finish && ft_strchr(" \t\n\v\f\r", str[*i]))
		return (-1);
	else if (!infos->is_quote && str[*i] == '\'')
		return (infos->flag = 1, infos->pos = *i, infos->is_quote = 1,
			quote_len(str, infos));
	else if (!infos->is_quote && str[*i] == '\"')
		return (infos->flag = 2, infos->pos = *i, infos->is_quote = 2,
			quote_len(str, infos));
	else if (!ft_strchr(" \t\n\v\f\r><|", str[*i]) && (str[*i + 1] == '\"'
			|| str[*i + 1] == '\''))
		return (infos->pos = *i + 1, ++(*len));
	else if ((ft_strchr("<>|", str[*i + 1]) || ft_strchr("|", str[*i]))
		&& str[*i + 1])
	{
		if ((str[*i] == '>' && str[*i + 1] == '>') || (str[*i] == '<' && str[*i
					+ 1] == '<'))
		{
			(*len)++;
			(*i)++;
		}
		(*len)++;
		(*i)++;
		return (-1);
	}
	return (-2);
}

int	word_len(char *str, t_infos *infos)
{
	int	i;
	int	len;
	int	c;

	len = 0;
	i = infos->pos;
	if (ft_strchr(" \t\n\v\f\r", str[i]))
		return (white_sp(str, infos));
	while (str[i])
	{
		if (ft_strchr("<>", str[i]) && !ft_strchr(" \t\n\v\f\r><|", str[i + 1]))
			return ((infos->pos) = i + 1, 1);
		c = conditions(infos, str, &i, &len);
		if (c >= -1)
		{
			if (c < 0)
				break ;
			else
				return (c);
		}
		len++;
		i++;
	}
	infos->pos = i;
	return (len);
}

void	init_args(t_infos *infos)
{
	infos->is_quote = 0;
	infos->is_finish = 0;
	infos->len = 0;
	infos->flag = 0;
	infos->n_pipes = 0;
	infos->pos = 0;
	infos->start = 0;
	infos->index = 0;
	infos->n_red = 0;
}

int	count_red(t_data *lst_words)
{
	int	count;

	count = 0;
	while (lst_words)
	{
		if (lst_words->type >= r_redirect && lst_words->type <= append)
			count++;
		lst_words = lst_words->next;
	}
	return (count);
}

int	is_expandable(t_data *lst_words)
{
	char	*val;

	while (lst_words && lst_words->type != pi_pe)
	{
		if ((lst_words->type == word || lst_words->type == dq_word)
			&& dollar_in(lst_words->word))
		{
			if (lst_words->next && lst_words->next->type != space)
				break ;
			val = set_value(lst_words->word, lst_words->infos->env);
			if (!ft_strcmp(val, "") || (space_in(val) && val[ft_strlen(val)
						- 1] != ' '))
				return (free(val), 0);
			else
				return (free(val), 1);
		}
		lst_words = lst_words->next;
	}
	return (1);
}
