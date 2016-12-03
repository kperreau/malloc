/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:50:17 by kperreau          #+#    #+#             */
/*   Updated: 2016/12/03 18:58:52 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

/*
**MALLOC VARS
*/
# define M 1000000
# define TINY_MAX 1024
# define TINY_SIZE (size_t)((2*M + getpagesize()) / getpagesize())*getpagesize()
# define SMALL_MAX 127000
# define SMALL_SIZE (size_t)((16*M + getpagesize())/getpagesize())*getpagesize()

/*
**MALLOC DEBUG COLORS
*/
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define COLOR_RESET "\x1b[0m"
# define COLOR_REV "\033[7;7m"

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
void			*reallocf(void *ptr, size_t size);
void			*calloc(size_t count, size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t nmemb, size_t size);
t_region		*init_regions(void);
t_page			*add_tiny(t_region *regions, size_t size);
t_page			*add_small(t_region *regions, size_t size);
t_page			*add_large(t_region *regions, size_t size);
t_region		*add_region(t_region *regions, t_page_type type, size_t lsize);
t_page_type		get_type_by_size(size_t size);
void			mem_copy(void *src, void *dest, size_t size);
void			ft_bzero(void *ptr, size_t size);
size_t			get_size_of_type(t_page_type type, t_region *region);
void			ft_putnbr(long n);
void			ft_putstr(const char *s);
void			get_name_of_region(t_page_type type);
void			show_alloc_mem(void);
void			show_alloc_mem_dump(void);
void			show_alloc_mem_str(void);
pthread_mutex_t	*ft_mutex(void);
void			ft_puthex(size_t n);

#endif
