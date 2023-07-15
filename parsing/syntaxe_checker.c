/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:00:13 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:54:53 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntaxe_checker(t_data *cmd_line)
{
	int	i;
	int	len;
	int	*types;

	i = 0;
	len = ft_lstsize(cmd_line);
	types = malloc(len * sizeof(int));
	while (cmd_line)
	{
		if (cmd_line->type != space)
		{
			types[i] = cmd_line->type;
			cmd_line = cmd_line->next;
			i++;
		}
		else
			cmd_line = cmd_line->next;
	}
	if (!check_for_errors(types, len))
		return (0);
	return (1);
}
