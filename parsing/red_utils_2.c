/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 04:55:42 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:55:24 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	vars_len(char **vars)
{
	int	i;

	i = 0;
	while (vars[i])
		i++;
	i += 2;
	return (i);
}

char	**delete_red(t_cmd_lines *lines)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!get_new_lenght(lines->cmd_line))
		return (NULL);
	tmp = malloc((get_new_lenght(lines->cmd_line) + 1) * sizeof(char *));
	while (lines->cmd_line[i])
	{
		if (is_red(lines->cmd_line[i]) && lines->cmd_line[i + 1])
			i += 2;
		else if (lines->cmd_line[i])
			tmp[j++] = ft_strdup(lines->cmd_line[i++]);
	}
	tmp[j] = NULL;
	return (tmp);
}

void	clean_lines(t_cmd_lines **lines)
{
	t_cmd_lines	*tmp;

	while (*lines)
	{
		tmp = *lines;
		*lines = (*lines)->next;
		if (tmp->cmd_line)
			freealloc2(tmp->cmd_line);
		free(tmp);
	}
}

int	strs_len(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdup2(char **strs)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc((strs_len(strs) + 1) * sizeof(char *));
	if (!new || !strs)
		return (new[i] = NULL, new);
	while (strs[i])
	{
		new[i] = ft_strdup(strs[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
