/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 16:40:01 by kperreau          #+#    #+#             */
/*   Updated: 2016/11/12 19:53:41 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

/*
**MALLOC VARS
*/
# define M 1000000
# define TINY_MAX 992
# define TINY_SIZE (int)((2*M + getpagesize()) / getpagesize()) *\
 getpagesize()

# define SMALL_MAX 127000
# define SMALL_SIZE (int)((16*M + getpagesize()) / getpagesize()) *\
 getpagesize()

/*
**PAGES
*/
typedef enum	e_page_type
{
	TINY,
	SMALL,
	LARGE
}				t_page_type;

typedef struct	s_region
{
	size_t			free_size;
	t_page_type		type;
	char			lock;
	struct s_region	*next;
	struct s_region	*prev;
	struct s_page	*page;
	struct s_page	*last_page;
}				t_region;

typedef struct	s_page
{
	size_t			size;
	char			is_free;
	void			*data;
	struct s_page	*next;
	struct s_page	*prev;
}				t_page;

t_region		*ft_singleton(void);
void			*malloc(size_t size);
void			free(void *ptr);
t_region		*init_regions(void);
t_page			*add_tiny(t_region *regions, size_t size);
t_page			*add_small(t_region *regions, size_t size);
t_page			*add_large(t_region *regions, size_t size);
t_region		*add_region(t_region *regions, t_page_type type, size_t lsize);
void			*realloc(void *ptr, size_t size);

#endif
