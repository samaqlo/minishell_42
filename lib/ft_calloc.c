/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astalha < astalha@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:56:54 by astalha           #+#    #+#             */
/*   Updated: 2022/10/24 00:10:55 by astalha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelm, size_t sizelm)
{
	void	*ptr;

	ptr = malloc (nelm * sizelm);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, nelm * sizelm);
	return (ptr);
}
