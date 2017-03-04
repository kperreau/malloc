/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:32:17 by kperreau          #+#    #+#             */
/*   Updated: 2017/01/05 16:55:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int			is_str(char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if ((*s < 32 || *s > 126) && *s != 10 && *s != 9 && *s != 13)
			return (0);
		++s;
		++len;
	}
	return (len);
}

static void			show_str(char *s, size_t size)
{
	size_t	i;
	size_t	len;

	ft_putstr(ANSI_COLOR_YELLOW);
	i = 0;
	while (i < size)
	{
		if ((len = is_str(s)) > 0)
		{
			ft_putstr(s);
			ft_putstr("\n");
		}
		i += len + 1;
		s += len + 1;
	}
	ft_putstr(COLOR_RESET);
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
				show_str(pages->data, pages->size);
			total += (long)pages->size;
		}
		pages = pages->next;
	}
	return (total);
}

void				show_alloc_mem_str(void)
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
