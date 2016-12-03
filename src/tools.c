/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:10:54 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page_type		get_type_by_size(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	else if (size > SMALL_MAX)
		return (LARGE);
	return (SMALL);
}

void			mem_copy(void *src, void *dst, size_t size)
{
	if (src != NULL && dst != NULL && size > 0)
	{
		pthread_mutex_lock(ft_mutex());
		while (size--)
			*(char*)dst++ = *(char*)src++;
		pthread_mutex_unlock(ft_mutex());
	}
}

size_t			get_size_of_type(t_page_type type, t_region *region)
{
	if (type == TINY)
		return (TINY_SIZE + sizeof(t_region));
	else if (type == SMALL)
		return (SMALL_SIZE + sizeof(t_region));
	else if (type == LARGE)
		return (region->page->size + sizeof(t_region));
	return (0);
}

void			ft_putstr(const char *s)
{
	size_t		i;

	i = 0;
	while (*(s + i))
		++i;
	write(1, s, i);
}

void			ft_putnbr(long n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}
