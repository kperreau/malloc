/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:42 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/12 20:05:25 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region			*ft_singleton(void)
{
	static t_region		*region = NULL;

	if ((region == NULL && (region = init_regions()) == NULL))
		return (NULL);
	return (region);
}

void	*malloc(size_t size)
{
	t_region		*region;
	void			*mem;

	region = ft_singleton();
	if (size < 1 || region == NULL)
		return (NULL);
	if (size <= TINY_MAX)
		mem = add_tiny(region, size);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		mem = add_small(region, size);
	else
		mem = add_large(region, size);
	return (mem);
}