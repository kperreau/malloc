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
	rtiny->free_size = TINY_SIZE - sizeof(t_page);
	rtiny->type = TINY;
	rtiny->prev = NULL;
	rtiny->next = NULL;
	rtiny->page = sizeof(t_region) + mem;
	rtiny->last_page = sizeof(t_region) + mem;
	ptiny = rtiny->page;
	ptiny->size = TINY_SIZE - sizeof(t_page);
	ptiny->is_free = 1;
	ptiny->data = sizeof(t_page) + (void*)ptiny;
	ptiny->prev = NULL;
	ptiny->next = NULL;
	return (rtiny);
}

static t_region		*init_region_small(void *mem)
{
	t_region			*rsmall;
	t_page				*psmall;

	rsmall = (t_region*)mem;
	rsmall->free_size = SMALL_SIZE - sizeof(t_page);
	rsmall->type = SMALL;
	rsmall->prev = NULL;
	rsmall->next = NULL;
	rsmall->page = sizeof(t_region) + mem;
	rsmall->last_page = sizeof(t_region) + mem;
	psmall = rsmall->page;
	psmall->size = SMALL_SIZE - sizeof(t_page);
	psmall->is_free = 1;
	psmall->data = sizeof(t_page) + (void*)psmall;
	psmall->prev = NULL;
	psmall->next = NULL;
	return (rsmall);
}

static t_region		*init_region_large(void *mem, size_t size)
{
	t_region			*rlarge;
	t_page				*plarge;

	rlarge = (t_region*)mem;
	rlarge->free_size = size;
	rlarge->type = LARGE;
	rlarge->prev = NULL;
	rlarge->next = NULL;
	rlarge->page = sizeof(t_region) + mem;
	rlarge->last_page = sizeof(t_region) + mem;
	plarge = rlarge->page;
	plarge->size = size;
	plarge->is_free = 1;
	plarge->data = sizeof(t_page) + (void*)plarge;
	plarge->prev = NULL;
	plarge->next = NULL;
	return (rlarge);
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
	else
		regions->next = init_region_large(mem, lsize);
	regions->next->prev = regions;
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
	regions->next->prev = regions;
	return (mem);
}
