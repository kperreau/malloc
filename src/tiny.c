/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:05:05 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/11 17:30:29 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page		*find_tiny_page(t_page *pages, size_t size)
{
	while (pages != NULL)
	{
		if (pages->is_free && pages->size >= sizeof(t_page) + size)
			return (pages);
		pages = pages->next;
	}
	return (NULL);
}

static t_page		*find_tiny_region(t_region *regions, size_t size)
{
	t_page		*page;

	while (regions != NULL)
	{
		if (regions->type == TINY &&
			regions->free_size >= sizeof(t_page) + size)
		{
			page = find_tiny_page(regions->page, size);
			if (page != NULL)
				return (page);
		}
		regions = regions->next;
	}
	return (NULL);
}

static t_page		*add_tiny_init(t_region *regions, t_page *page, size_t size)
{
	if (page->next == NULL && (void*)page + sizeof(t_page) < (void*)regions \
		+ TINY_SIZE + sizeof(t_page))
	{
		page->next = sizeof(t_page) + (void*)page + size;
		page->next->next = NULL;
		page->next->prev = page;
		page->next->is_free = 1;
		page->next->size = page->size - (size + sizeof(t_page));
		page->next->data = sizeof(t_page) + (void*)page->next;
	}
	page->is_free = 0;
	page->size = size;
	return (page);
}

t_page				*add_tiny(t_region *regions, size_t size)
{
	t_page		*page;
	t_region	*new_region;

	page = find_tiny_region(regions, size);
	if (page == NULL)
	{
		//new_region = add_region(regions, TINY, size);
		//page = new_region->page;
	}
	regions->free_size -= sizeof(t_page) + size;
	add_tiny_init(regions, page, size);
	return (page->data);
}
