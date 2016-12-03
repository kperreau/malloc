/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:03:25 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			free_page2(t_region *region, t_page *page)
{
	if (page->next)
		page->size = (size_t)(page->next) - ((size_t)page + sizeof(t_page));
	else
	{
		page->size = ((size_t)region + get_size_of_type(region->type, region))\
	- ((size_t)page + sizeof(t_page));
		region->last_page = page;
	}
	page->is_free = 1;
	region->free_size = 1;
}

static int			free_page1(t_region *region, t_page *page)
{
	if (region->type == LARGE)
	{
		region->prev->next = region->next;
		if (region->next)
			region->next->prev = region->prev;
		munmap((void*)region, region->page->size + sizeof(t_page) + \
	sizeof(t_region));
		return (0);
	}
	if (page->prev && page->prev->is_free)
	{
		page->prev->next = page->next;
		page = page->prev;
		if (page->next)
			page->next->prev = page;
	}
	if (page->next && page->next->is_free)
	{
		page->next = page->next->next;
		if (page->next)
			page->next->prev = page;
	}
	free_page2(region, page);
	return (0);
}

static t_page		*search_page(t_page *pages)
{
	if (!pages->is_free && pages->data - sizeof(t_page) == pages
		&& (pages->next == NULL || pages->next->prev == pages)
		&& (pages->prev == NULL || pages->prev->next == pages))
	{
		return (pages);
	}
	return (NULL);
}

static int			search_region(t_region *regions, void *ptr)
{
	t_page		*page;

	while (regions != NULL)
	{
		if (ptr > (void*)regions && ptr <= (void*)regions->last_page +\
	sizeof(t_page))
		{
			page = search_page(ptr - sizeof(t_page));
			if (page != NULL)
			{
				free_page1(regions, page);
				return (1);
			}
		}
		regions = regions->next;
	}
	return (0);
}

void				free(void *ptr)
{
	t_region		*region;

	if (ptr != NULL)
	{
		region = ft_singleton();
		pthread_mutex_lock(ft_mutex());
		search_region(region, ptr);
		pthread_mutex_unlock(ft_mutex());
	}
}
