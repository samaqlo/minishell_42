/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:34:26 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 13:14:38 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_spaces(t_data *words)
{
	while (words)
	{
		if (words->type != space)
			return (0);
		words = words->next;
	}
	return (1);
}

int	quoting_checker(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (!flag && ft_strchr(";&\\", str[i]))
			return (print_error(2, 0), 3);
		if (str[i] == '\'')
		{
			if (!flag)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		else if (str[i] == '\"')
		{
			if (!flag)
				flag = 2;
			else if (flag == 2)
				flag = 0;
		}
	}
	return (flag);
}

int	strat_end_checker(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (ft_putstr_fd(
				"minishell: syntax error near unexpected token `|\'\n", 2), 0);
	i = ft_strlen(str) - 1;
	if (ft_strchr("><|", str[i]))
		return (ft_putstr_fd(
				"minishell: syntax error near unexpected token `newline\'\n",
				2), 0);
	return (1);
}

int	quote_len(char *str, t_infos *infos)
{
	int	i;
	int	len;

	i = infos->pos + 1;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' && infos->is_quote == 1)
			break ;
		else if (str[i] == '\"' && infos->is_quote == 2)
			break ;
		else
		{
			len++;
			i++;
		}
	}
	i++;
	infos->pos = i;
	return (len);
}

int	white_sp(char *str, t_infos *infos)
{
	int	i;
	int	len;

	i = infos->pos;
	len = 0;
	while (ft_strchr(" \t\n\v\f\r", str[i]))
	{
		len++;
		i++;
	}
	infos->flag = 3;
	infos->pos = i;
	return (len);
}
