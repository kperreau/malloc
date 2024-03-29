/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:05:05 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:00:42 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_page		*add_large_init(t_region *region, t_page *page, size_t size)
{
	page->is_free = 0;
	page->size = size;
	region->free_size = 0;
	return (page);
}

t_page				*add_large(t_region *regions, size_t size)
{
	t_page		*page;
	t_region	*region;

	region = add_region(regions, LARGE, size);
	page = region->page;
	page = add_large_init(region, page, size);
	return (page->data);
}
