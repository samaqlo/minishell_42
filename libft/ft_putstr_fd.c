/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 04:49:07 by astalha           #+#    #+#             */
/*   Updated: 2023/05/22 22:54:45 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd (*(s++), fd);
}
void	ft_putstr_fd_edit(char *s, char *s2, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd (*(s++), fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd("\'\n", fd);
	free(s2);
}
