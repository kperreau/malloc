/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 19:42:43 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/12 20:11:31 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page		*find_small_page(t_page *pages, size_t size)
{
	while (pages != NULL)
	{
		if (pages->is_free && pages->size >= sizeof(t_page) + size)
			return (pages);
		pages = pages->next;
	}
	return (NULL);
}

static void		*find_small_region(t_region *regions, size_t size, void *ret[2])
{
	t_page		*page;

	while (regions != NULL)
	{
		if (regions->type == SMALL &&
			regions->free_size >= sizeof(t_page) + size)
		{
			page = find_small_page(regions->page, size);
			if (page != NULL)
			{
				ret[0] = page;
				ret[1] = regions;
				return (ret);
			}
		}
		regions = regions->next;
	}
	return (NULL);
}

static t_page		*add_small_init(t_region *regions, t_page *page, size_t size)
{
	if (page->next == NULL && (void*)page + sizeof(t_page) < (void*)regions \
		+ SMALL_SIZE + sizeof(t_page))
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
	cregion->free_size -= sizeof(t_page) + size;
	add_small_init(cregion, page, size);
	return (page->data);
}
