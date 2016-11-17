/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:06:58 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/11 17:06:59 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_region		*region ;

	ptr = malloc(size);
	// if (ptr != NULL)
	// {
		// region = ft_singleton();
		// exit(-1);
		// if (region == NULL || search_region(region, ptr) == 0)
		// {
			// write(2, "Error.\n", 7);
			// exit(-1);
		// }
	// }
	return (ptr);
}
