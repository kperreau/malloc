/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:26:29 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/28 17:27:08 by kperreau         ###   ########.fr       */
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
			regions->lfree_size >= sizeof(t_page) + size)
		{
			page = find_tiny_page(regions->page, size);
			if (page != NULL)
				return (page);
		}
		regions = regions->next;
	}
	return (NULL);
}

static t_page				*add_tiny_init(t_page *page, size_t size)
{
	page->next = sizeof(t_page) + (void*)page + size;
	page->next->next = NULL;
	page->next->prev = page;
	page->next->is_free = 1;
	page->next->size = page->size - (size + sizeof(t_page));
	page->next->data = sizeof(t_page) + (void*)page->next;
	page->is_free = 0;
	page->size = size;
}

t_page				*add_tiny(t_region *regions, size_t size)
{
	t_page		*page;

	page = find_tiny_region(regions, size);
	// fprintf(stderr, "ptr: %s\n", page->data);
	if (page == NULL)
		return (NULL);
	add_tiny_init(page, size);
	return (page->data);
}