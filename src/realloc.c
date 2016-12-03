/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:04:22 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	int			result;

	result = 0;
	while (regions != NULL)
	{
		if (ptr > (void*)regions && ptr <= (void*)regions->last_page + \
	sizeof(t_page))
		{
			result = 1;
			page = search_page(ptr - sizeof(t_page));
			if (page != NULL)
			{
				ret[0] = regions;
				ret[1] = page;
				return (2);
			}
		}
		regions = regions->next;
	}
	return (result);
}

static void			*build_realloc(t_region *region, t_page *page\
	, size_t size, void *ptr)
{
	void	*new_ptr;

	new_ptr = NULL;
	pthread_mutex_lock(ft_mutex());
	if (get_type_by_size(size) != region->type || size > page->size)
	{
		pthread_mutex_unlock(ft_mutex());
		new_ptr = malloc(size);
		mem_copy(ptr, new_ptr, page->size < size ? page->size : size);
		free(ptr);
		return (new_ptr);
	}
	pthread_mutex_unlock(ft_mutex());
	if (size <= page->size)
	{
		mem_copy(ptr, new_ptr, size);
		pthread_mutex_lock(ft_mutex());
		page->size = size;
		pthread_mutex_unlock(ft_mutex());
		return (ptr);
	}
	return (ptr);
}

void				*reallocf(void *ptr, size_t size)
{
	t_region		*region;
	void			*ret[2];
	int				result;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	region = ft_singleton();
	pthread_mutex_lock(ft_mutex());
	result = search_region(region, ptr, ret);
	pthread_mutex_unlock(ft_mutex());
	if (result == 1)
		return (malloc(size));
	if (result == 0)
		return (malloc(size));
	ptr = build_realloc(ret[0], ret[1], size, ptr);
	return (ptr);
}

void				*realloc(void *ptr, size_t size)
{
	t_region		*region;
	void			*ret[2];
	int				result;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	region = ft_singleton();
	pthread_mutex_lock(ft_mutex());
	result = search_region(region, ptr, ret);
	pthread_mutex_unlock(ft_mutex());
	if (result == 1)
		return (NULL);
	if (result == 0)
		return (ptr);
	ptr = build_realloc(ret[0], ret[1], size, ptr);
	return (ptr);
}
