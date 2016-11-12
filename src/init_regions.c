/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_regions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:05:25 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/12 20:09:04 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_region		*init_region_tiny(void *mem)
{
	t_region			*rtiny;
	t_page				*ptiny;

	rtiny = (t_region*)mem;
	rtiny->free_size = TINY_SIZE;
	rtiny->type = TINY;
	rtiny->prev = NULL;
	rtiny->next = NULL;
	rtiny->page = sizeof(t_region) + mem;
	ptiny = rtiny->page;
	ptiny->size = TINY_SIZE;
	ptiny->is_free = 1;
	ptiny->data = sizeof(t_page) + (void*)rtiny;
	ptiny->prev = NULL;
	ptiny->next = NULL;
	return (rtiny);
}

static t_region		*init_region_small(void *mem)
{
	t_region			*rsmall;
	t_page				*psmall;

	rsmall = (t_region*)mem;
	rsmall->free_size = SMALL_SIZE;
	rsmall->type = SMALL;
	rsmall->prev = NULL;
	rsmall->next = NULL;
	rsmall->page = sizeof(t_region) + mem;
	psmall = rsmall->page;
	psmall->size = SMALL_SIZE;
	psmall->is_free = 1;
	psmall->data = sizeof(t_page) + (void*)rsmall;
	psmall->prev = NULL;
	psmall->next = NULL;
	return (rsmall);
}

t_region			*add_region(t_region *regions, t_page_type type\
	, size_t lsize)
{
	size_t		size;
	void		*mem;

	while (regions->next != NULL)
		regions = regions->next;
	if (type == LARGE)
		size = lsize + sizeof(t_region) + sizeof(t_page);
	else
		size = ((type == TINY) ? TINY_SIZE : SMALL_SIZE) + sizeof(t_region);
	mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (type == TINY)
		regions->next = init_region_tiny(mem);
	else if (type == SMALL)
		regions->next = init_region_small(mem);
	return (regions->next);
}

t_region			*init_regions(void)
{
	void		*mem;
	size_t		size;
	t_region	*regions;

	size = sizeof(t_region) * 2 + TINY_SIZE + SMALL_SIZE;
	mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem == NULL)
		return (NULL);
	regions = init_region_tiny(mem);
	regions->next = init_region_small(mem + sizeof(t_region) + TINY_SIZE);
	return (mem);
}
