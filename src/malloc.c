/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:42 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 19:01:26 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region			*ft_singleton(void)
{
	static t_region		*region = NULL;

	if (region == NULL && (region = init_regions()) == NULL)
		return (NULL);
	return (region);
}

pthread_mutex_t		*ft_mutex(void)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&mutex);
}

void				*malloc(size_t size)
{
	t_region		*region;
	void			*mem;

	region = ft_singleton();
	if (size < 1 || region == NULL)
		return (NULL);
	pthread_mutex_lock(ft_mutex());
	if (size <= TINY_MAX)
		mem = add_tiny(region, size);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		mem = add_small(region, size);
	else
		mem = add_large(region, size);
	pthread_mutex_unlock(ft_mutex());
	return (mem);
}
