# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 14:18:45 by cpireyre          #+#    #+#              #
#    Updated: 2018/11/25 09:46:43 by cpireyre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	gcc
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror -O2
LIBDIR	:=	./libft
LIBFT	:=	$(LIBDIR)/libft.a
BFLAGS	:=	-I$(LIBDIR)/
#DEBUG	:=	-g3 -fsanitize=address -fsanitize=undefined 
INCLUDE	:=	-lft -L$(LIBDIR)/
NAME	:=	lem-in

C_FILES		:=	parse.c lem_in.c mem.c print.c rooms.c pipes.c \
	count.c graph.c edmonds_karp.c splitcheck.c \
	sender.c main.c traverse.c paths.c
H_FILES		:=	lem_in.h 
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
	@sh lem-bench.sh
	@make big
	@make super
	@$(RM) bench.out a.out a

big: all
	@echo "\x1b[4mTesting run time on --big...\x1b[0m"
	@./tests/generator --big > a
	@grep -m 1 required < a
	@time ./lem-in < a > a.out
	@grep L < a.out | wc -l

super: all
	@echo "\x1b[4mTesting run time on --big-superposition...\x1b[0m"
	@./tests/generator --big-superposition > a
	@grep -m 1 required < a
	@time ./lem-in < a > a.out
	@grep L < a.out | wc -l
	
.PHONY: all, re, clean, fclean, force, run, urn, tags, thousand, one, big, super, test
