/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:54:55 by astalha           #+#    #+#             */
/*   Updated: 2023/06/23 12:48:35 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **av, int i, int fd)
{
	int	test;

	test = 1;
	if (av[i][0])
	{
		if (check_n(av[i]))
		{
			ft_putstr_fd(av[i], fd);
			test = 0;
			if (av[i + 1])
				ft_putstr_fd(" ", fd);
		}
		if (!test && !check_n(av[i]))
		{
			ft_putstr_fd(av[i], fd);
			if (av[i + 1])
				ft_putstr_fd(" ", fd);
		}
	}
}

int	built_echo(char **av, int fd)
{
	int	i;

	i = 1;
	if (!av[1] || (!ft_strcmp(av[1], "")))
		return (ft_putstr_fd("\n", fd), 1);
	while (av[i])
	{
		ft_echo(av, i, fd);
		i++;
	}
	if (av[1] && check_n(av[1]))
		ft_putstr_fd("\n", fd);
	return (1);
}
