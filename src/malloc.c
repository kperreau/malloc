/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:26:29 by kperreau          #+#    #+#             */
/*   Updated: 2016/10/28 17:44:32 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*mem;

	write(1, "a", 1);
	if (size < 1)
		return (NULL);
	mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (mem);
}
