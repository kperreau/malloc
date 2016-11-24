/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/24 19:29:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*void				*calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb <= 0 || size <= 0)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem != NULL)
		ft_bzero(mem, nmemb * size);
	return (mem);
}*/

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

static int			search_region(t_region *regions, void *ptr, void *ret[2])
{
	t_page		*page;

	while (regions != NULL)
	{
		if (ptr > (void*)regions && ptr <= (void*)regions->last_page + sizeof(t_page))
		{
			page = search_page(ptr - sizeof(t_page));
			if (page != NULL)
			{
				ret[0] = regions;
				ret[1] = page;
				return (1);
			}
		}
		regions = regions->next;
	}
	return (0);
}

static void			*build_realloc(t_region *region, t_page *page, size_t size, void *ptr)
{
	void	*new_ptr;

	// if (get_type_by_size(size) != region->type)
	{
		new_ptr = malloc(size);
		mem_copy(ptr, new_ptr, page->size < size ? page->size : size);
		free(ptr);
		return (new_ptr);
	}
	return (ptr);
}

void				*realloc(void *ptr, size_t size)
{
	t_region		*region ;
	void			*ret[2];

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	region = ft_singleton();
	if (region == NULL || search_region(region, ptr, ret) == 0)
	{
		//write(2, "Error.\n", 7);
		//exit(-1);
	}
	ptr = build_realloc(ret[0], ret[1], size, ptr);
	return (ptr);
}
