/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/11 17:06:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t		get_size_of_type(t_page_type type, t_region *region)
{
	if (type == TINY)
		return (TINY_SIZE);
	else if (type == SMALL)
		return (SMALL_SIZE);
	else
		return (region->page->size);
	return (0);
}
/*
static t_page		*search_page(t_page *pages, void *ptr)
{
	while (pages != NULL)
	{
		if (!pages->is_free && ptr == pages->data)
		{
			pages->is_free = 1;
			return (pages);
		}
		pages = pages->next;
	}
	return (NULL);
}

static int			search_region(t_region *regions, void *ptr)
{
	t_page		*page;

	while (regions != NULL)
	{
		if (ptr > (void*)regions && ptr < (void*)regions + get_size_of_type(regions->type))
		{
			page = search_page(regions->page, ptr);
			if (page != NULL)
			{
				regions->free_size += page->size;
				return (1);
			}
		}
		regions = regions->next;
	}
	return (0);
}
*/

static t_page		*search_page(t_page *pages)
{
	if (!pages->is_free && pages->data - sizeof(t_page) == pages
		&& (pages->next == NULL
		|| pages->next->prev == pages->data - sizeof(t_page))
		&& (pages->prev == NULL
		|| pages->prev->next == pages->data - sizeof(t_page)))
	{
		pages->is_free = 1;
		return (pages);
	}
	return (NULL);
}

static int			search_region(t_region *regions, void *ptr)
{
	t_page		*page;

	while (regions != NULL)
	{
		if (ptr > (void*)regions && ptr < (void*)regions + get_size_of_type(regions->type, regions))
		{
			page = search_page(ptr - sizeof(t_page));
			if (page != NULL)
			{
				regions->free_size += page->size;
				if (regions->type == LARGE)
				{
					regions->prev->next = regions->next;
					if (regions->next)
						regions->next->prev = regions->prev;
					munmap((void*)regions, (size_t)regions + regions->page->size + sizeof(t_page) + sizeof(t_region));
				}
				return (1);
			}
		}
		regions = regions->next;
	}
	return (0);
}

void				free(void *ptr)
{
	t_region		*region ;

	if (ptr != NULL)
	{
		region = ft_singleton();
		if (region == NULL || search_region(region, ptr) == 0)
		{
			write(2, "Error.\n", 7);
			exit(-1);
		}
	}
}
