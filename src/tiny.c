/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:05:05 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/27 17:36:42 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page		*find_tiny_page(t_page *pages, size_t size)
{
	while (pages != NULL)
	{
		if (pages->is_free && pages->size >= size)
			return (pages);
		pages = pages->prev;
	}
	return (NULL);
}

static void		*find_tiny_region(t_region *regions, size_t size, void *ret[2])
{
	t_page		*page;

	while (regions != NULL)
	{
		if (regions->type == TINY && regions->free_size) //&& regions->free_size >= size)
		{
			page = find_tiny_page(regions->last_page, size);
			if (page != NULL)
			{
				ret[0] = page;
				ret[1] = regions;
				return (ret);
			}
			regions->free_size = 0; //1
		}
		regions = regions->next;
	}
	return (NULL);
}

static t_page		*add_tiny_init(t_page *page, size_t size, t_region *cregion)
{
	t_page		*npage;

	if (page->next == NULL && (void*)page + size + sizeof(t_page) < \
		(void*)cregion + TINY_SIZE)
	{
		npage = (void*)page + sizeof(t_page) + size;
		npage->next = NULL;
		npage->prev = page;
		page->next = npage;
		npage->is_free = 1;
		npage->size = page->size - (size + sizeof(t_page));
		npage->data = sizeof(t_page) + (void*)npage;
		cregion->last_page = npage;
		// cregion->free_size -= sizeof(t_page);
		cregion->free_size = 1; // 1
	}
	else if (page->next && size < page->size && page->size - size > sizeof(t_page))
	{
		npage = (void*)page + sizeof(t_page) + size;
		npage->next = page->next;
		npage->prev = page;
		page->next = npage;
		npage->next->prev = npage;
		npage->is_free = 1;
		npage->size = page->size - (size + sizeof(t_page));
		npage->data = sizeof(t_page) + (void*)npage;
		cregion->free_size -= sizeof(t_page);
		cregion->free_size = 1; // 1
	}
	page->is_free = 0;
	page->size = size;
	return (page);
}

t_page				*add_tiny(t_region *regions, size_t size)
{
	t_page		*page;
	t_region	*cregion;
	void		*ret[2];

	if (find_tiny_region(regions, size, ret) != NULL)
	{
		page = ret[0];
		cregion = ret[1];
	}
	else
	{
		cregion = add_region(regions, TINY, size);
		page = cregion->page;
	}
	add_tiny_init(page, size, cregion);
	return (page->data);
}
