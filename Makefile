# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 14:18:45 by cpireyre          #+#    #+#              #
#    Updated: 2018/11/21 15:15:11 by cpireyre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	gcc
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror
LIBDIR	:=	./libft
LIBFT	:=	$(LIBDIR)/libft.a
BFLAGS	:=	-I$(LIBDIR)/
DEBUG	:=	-g3 -fsanitize=address -fsanitize=undefined 
INCLUDE	:=	-lft -L$(LIBDIR)/
NAME	:=	lem-in

C_FILES		:=	parse.c lem_in.c mem.c print.c rooms.c pipes.c \
	count.c graph.c edmonds_karp.c splitcheck.c \
	sender.c main.c traverse.c paths.c
H_FILES		:=	lem_in.h graph.h
OBJ			:=	$(C_FILES:.c=.o)

DEPS		=	$(H_FILES) Makefile 

all: $(NAME)

$(LIBFT): force
	@$(MAKE) -C $(LIBDIR) 2> /dev/null

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(BFLAGS) $< -c -o $@ $(DEBUG)

$(NAME): $(DEPS) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(BFLAGS) $(OBJ) $(INCLUDE) $(DEBUG) -o $@
	#ctags -R # for ease of navigation with vim

clean:
	$(MAKE) clean -C $(LIBDIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C libft/
	$(RM) $(NAME)
	$(RM) tags

re: fclean all

force:
	@true # to shut up libft Makefile

run: $(NAME)
	./lem-in < tests/fucked_up

urn: run # typos will happen

tags: all
	ctags -R

test: $(NAME)
	sh ./tests/test_basic_parse.sh

.PHONY: all, re, clean, fclean, force, run, urn, tags
