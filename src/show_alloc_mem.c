/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:42 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:10:24 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			show_hex(void *data, size_t size)
{
	size_t	i;

	ft_putstr(ANSI_COLOR_YELLOW);
	i = 0;
	ft_putstr(ANSI_COLOR_YELLOW);
	while (i < size)
		ft_puthex(*(char *)(data + i++));
	ft_putstr(COLOR_RESET);
	ft_putstr("\n");
	ft_putstr(COLOR_RESET);
}

void				get_name_of_region(t_page_type type)
{
	if (type == TINY)
		ft_putstr("TINY : 0x");
	else if (type == SMALL)
		ft_putstr("SMALL : 0x");
	else if (type == LARGE)
		ft_putstr("LARGE : 0x");
	else
		ft_putstr("UNKNOWN : 0x");
}

static long			show_alloc_mem_pages(t_page *pages, int data)
{
	long		total;

	total = 0;
	while (pages)
	{
		if (!pages->is_free)
		{
			ft_puthex((size_t)pages->data);
			ft_putstr(" - ");
			ft_puthex((size_t)(pages->data) + pages->size);
			ft_putstr(" : ");
			ft_putnbr((size_t)pages->size);
			ft_putstr(" octets\n");
			if (data)
				show_hex(pages->data, pages->size);
			total += (long)pages->size;
		}
		pages = pages->next;
	}
	return (total);
}

void				show_alloc_mem_dump(void)
{
	t_region		*regions;
	long			total;

	total = 0;
	regions = ft_singleton();
	pthread_mutex_lock(ft_mutex());
	while (regions)
	{
		ft_putstr(ANSI_COLOR_CYAN);
		ft_putstr(COLOR_REV);
		get_name_of_region(regions->type);
		ft_puthex((size_t)regions);
		ft_putstr(COLOR_RESET);
		ft_putstr("\n");
		total += show_alloc_mem_pages(regions->page, 1);
		regions = regions->next;
	}
	pthread_mutex_unlock(ft_mutex());
	ft_putstr(ANSI_COLOR_RED);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	ft_putstr(COLOR_RESET);
}

void				show_alloc_mem(void)
{
	t_region		*regions;
	long			total;

	total = 0;
	regions = ft_singleton();
	pthread_mutex_lock(ft_mutex());
	while (regions)
	{
		get_name_of_region(regions->type);
		ft_puthex((size_t)regions);
		ft_putstr("\n");
		total += show_alloc_mem_pages(regions->page, 0);
		regions = regions->next;
	}
	pthread_mutex_unlock(ft_mutex());
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
