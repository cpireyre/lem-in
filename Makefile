# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 14:18:45 by cpireyre          #+#    #+#              #
#    Updated: 2018/12/05 14:24:08 by cpireyre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	gcc
RM		:=	rm -f
CFLAGS	:=	-Wall -Wextra -Werror
LIBDIR	:=	./libft
LIBFT	:=	$(LIBDIR)/libft.a
BFLAGS	:=	-I$(LIBDIR)/ -Iinclude
#DEBUG	:=	-g3 #-fsanitize=address -fsanitize=undefined -Og
INCLUDE	:=	-lft -L$(LIBDIR)/ 
NAME	:=	lem-in

SRC_PATH		= 	./src/
SRC_NAME	:=	parse.c lem_in.c mem.c print.c rooms.c pipes.c \
	count.c graph.c edmonds_karp.c splitcheck.c \
	sender.c main.c paths.c trajectory.c initsender.c
SRC				=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ_PATH	:= 	./obj/
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_NAME	=	$(SRC_NAME:.c=.o)

DEPS		=	$(H_FILES) Makefile 

all: $(NAME)

$(LIBFT): force
	@$(MAKE) -C $(LIBDIR) 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(BFLAGS) $< -c -o $@ $(DEBUG)

$(NAME): $(DEPS) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(BFLAGS) $(OBJ) $(INCLUDE) $(DEBUG) -o $@
	#ctags -R # for ease of navigation with vim

clean:
	$(MAKE) clean -C $(LIBDIR)
	$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

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
	@$(RM) bench.out

big: all
	@echo "\x1b[4mTesting run time on --big...\x1b[0m"
	@./tests/generator --big > a
	@grep -m 1 required < a
	@time ./lem-in < a > a.out
	@grep L < a.out | wc -l
	@$(RM) a.out a

super: all
	@echo "\x1b[4mTesting run time on --big-superposition...\x1b[0m"
	@./tests/generator --big-superposition > a
	@grep -m 1 required < a
	@time ./lem-in < a > a.out
	@grep L < a.out | wc -l
	@$(RM) a.out a
	
.PHONY: all, re, clean, fclean, force, run, urn, tags, thousand, one, big, super, test
