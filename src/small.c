/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 19:42:43 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:20:57 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page		*find_small_page(t_page *pages, size_t size)
{
	while (pages != NULL)
	{
		if (pages->is_free && pages->size >= size)
			return (pages);
		pages = pages->prev;
	}
	return (NULL);
}

static void			*find_small_region(t_region *regions, size_t size\
	, void *ret[2])
{
	t_page		*page;

	while (regions != NULL)
	{
		if (regions->type == SMALL && regions->free_size)
		{
			page = find_small_page(regions->last_page, size);
			if (page != NULL)
			{
				ret[0] = page;
				ret[1] = regions;
				return (ret);
			}
			regions->free_size = 0;
		}
		regions = regions->next;
	}
	return (NULL);
}

static void			sub_add_small_init(t_page *page, size_t size\
	, t_region *cregion)
{
	t_page		*npage;

	npage = (void*)page + sizeof(t_page) + size;
	npage->next = page->next;
	npage->prev = page;
	page->next = npage;
	npage->next->prev = npage;
	npage->is_free = 1;
	npage->size = page->size - (size + sizeof(t_page));
	npage->data = sizeof(t_page) + (void*)npage;
	cregion->free_size = 1;
}

static t_page		*add_small_init(t_page *page, size_t size, \
	t_region *cregion)
{
	t_page		*npage;

	if (page->next == NULL && (void*)page + size + sizeof(t_page) < \
		(void*)cregion + SMALL_SIZE)
	{
		npage = (void*)page + sizeof(t_page) + size;
		npage->next = NULL;
		npage->prev = page;
		page->next = npage;
		npage->is_free = 1;
		npage->size = page->size - (size + sizeof(t_page));
		npage->data = sizeof(t_page) + (void*)npage;
		cregion->last_page = npage;
		cregion->free_size = 1;
	}
	else if (page->next && size < page->size && page->size - size > \
	sizeof(t_page))
		sub_add_small_init(page, size, cregion);
	page->is_free = 0;
	page->size = size;
	return (page);
}

t_page				*add_small(t_region *regions, size_t size)
{
	t_page		*page;
	t_region	*cregion;
	void		*ret[2];

	if (find_small_region(regions, size, ret) != NULL)
	{
		page = ret[0];
		cregion = ret[1];
	}
	else
	{
		cregion = add_region(regions, SMALL, size);
		page = cregion->page;
	}
	add_small_init(page, size, cregion);
	return (page->data);
}
