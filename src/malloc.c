/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:42 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/27 21:24:01 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region			*ft_singleton(void)
{
	static t_region		*region = NULL;

	if (region == NULL && (region = init_regions()) == NULL)
		return (NULL);
	return (region);
}

pthread_mutex_t		*ft_mutex(void)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	return (&mutex);
}

void				*malloc(size_t size)
{
	t_region		*region;
	void			*mem;

	//show_alloc_mem();
	region = ft_singleton();
	if (size < 1 || region == NULL)
		return (NULL);
	//pthread_mutex_lock (ft_mutex());
	if (size <= TINY_MAX)
		mem = add_tiny(region, size);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		mem = add_small(region, size);
	else
		mem = add_large(region, size);
	//pthread_mutex_unlock (ft_mutex());
	return (mem);
}

void				show_alloc_mem(void)
{
	t_region		*regions;
	t_page			*pages;

	regions = ft_singleton();
	while (regions)
	{
		ft_putstr("-- Region --\n\n");
		ft_putstr("Type: ");
		ft_putnbr((size_t)regions->type);
		ft_putstr("\n");
		ft_putstr("Regions ptr: ");
		ft_putnbr((size_t)regions);
		ft_putstr("\n");
		ft_putstr("Free size: ");
		ft_putnbr((size_t)regions->free_size);
		ft_putstr("\n\n");
		ft_putstr("-- Pages --\n\n");
		pages = regions->page;
		while (pages)
		{
			ft_putstr("Page size: ");
			ft_putnbr((size_t)pages->size);
			ft_putstr("\n");
			ft_putstr("Is free: ");
			ft_putnbr((size_t)pages->is_free);
			ft_putstr("\n");
			ft_putstr("Data ptr: ");
			ft_putnbr((size_t)pages->data);
			ft_putstr("\n");
			ft_putstr("Data value: ");
			ft_putstr(pages->data);
			ft_putstr("\n");
			ft_putstr("Next: ");
			ft_putnbr((size_t)pages->next);
			ft_putstr("\n");
			ft_putstr("Prev: ");
			ft_putnbr((size_t)pages->prev);
			ft_putstr("\n");
			ft_putstr("Page ptr: ");
			ft_putnbr((size_t)pages);
			ft_putstr("\n\n");
			pages = pages->next;
		}
		ft_putstr("-------\n\n");
		regions = regions->next;
	}
}
