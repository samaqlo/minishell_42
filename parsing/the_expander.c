/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 00:54:19 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 09:38:37 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_line(t_data *cmd_line)
{
	char	*tmp;
	int		start;
	int		i;
	int		j;
	t_data	*head;

	head = cmd_line;
	while (cmd_line)
	{
		i = 0;
		j = 0;
		cmd_line->vars = (char **)malloc((count_words(cmd_line->word) + 1)
				* sizeof(char *));
		while (cmd_line->word[i])
		{
			start = i;
			tmp = ft_substr(cmd_line->word, start, get_len(cmd_line->word, &i));
			fill_vars2(cmd_line, tmp, j, head);
			j++;
		}
		cmd_line->vars[j] = NULL;
		cmd_line = cmd_line->next;
	}
}

char	*two_to_one(char **vars)
{
	int		i;
	char	*line;
	char	*tmp;

	line = ft_strdup("");
	i = 0;
	while (vars[i])
	{
		tmp = ft_strjoin(line, vars[i]);
		free(line);
		line = tmp;
		i++;
	}
	return (line);
}

void	the_fucking_expand(t_data *lst_words)
{
	split_line(lst_words);
	while (lst_words)
	{
		free(lst_words->word);
		lst_words->word = two_to_one(lst_words->vars);
		lst_words = lst_words->next;
	}
}
