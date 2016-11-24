# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2016/11/24 16:01:56 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

# Dir vars

SRCDIR = src

INCLUDESDIR = includes

# Files vars

CFILES = tools.c init_regions.c malloc.c free.c tiny.c small.c large.c realloc.c

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJ = $(SRC:.c=.o)

HFILES = malloc.h

HEADERS = $(patsubst %, $(INCLUDESDIR)/%, $(HFILES))

# COMPILATION

#ERRORFLAGS = -Wall -Werror -Wextra -W
ERRORFLAGS = 
# ERRORFLAGS = -march=native -Ofast

INCLUDEFLAGS = -I $(INCLUDESDIR)/

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS) 

CC = gcc

# Git vars

TOGIT =	$(SRC) \
		$(HEADERS) \
		Makefile \
		auteur \

# Rules

all: $(NAME)

$(NAME): $(OBJ)
#			@$(CC) $(FLAGS) $(OBJ) -fPIC -o $(NAME)
			@$(CC) $(FLAGS) $(OBJ) -fPIC -shared -o $(NAME)
			@ln -s $(NAME) libft_malloc.so

re: fclean all

clean:
			@rm -f $(OBJ)
			@rm -f libft_malloc.so
			@rm -f $(NAME)

fclean: clean
			@rm -f $(NAME)

%.o: %.c
#			@$(CC) -c $< $(FLAGS) -fPIC -shared -o $@
			@$(CC) -c $< $(FLAGS) -fPIC -o $@

git:
		git add $(TOGIT)
		git commit -m 'auto update'
		git push
