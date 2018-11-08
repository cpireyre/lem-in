/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 15:29:25 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define DEBUG		1

# define CONNECTED	4
# define START		2
# define END		3
# define NORMAL		1

typedef struct		s_rooms
{
	char			*name;
	t_byte			type;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_lemin
{
	int				ants;
	t_rooms			*rooms;
	char			**pipes;
}					t_lemin;

/*
**	parse.c
*/

t_bool				store_ants(t_list **head, t_lemin *lemin);
t_bool				add_room(t_rooms **map, char *input, t_byte type);
void				store_rooms(t_list **head, t_lemin *lemin);

/*
**	print.c
*/

void				print_rooms(t_rooms	*map);
void				print_list(t_list **head);

/*
**	rooms.c
*/

t_bool				check_room_coordinate(char **name);
t_bool				room_is_valid(char *name);
t_rooms				*new_room(char *name_ptr, t_byte type);
char				*get_room_name(char *input);

/*
**	pipes.c
*/

void				store_pipes(t_list **ptr, t_lemin *lemin);

/*
**	mem.c
*/

void				free_lemin(t_lemin *addr);
void				free_list(t_list **strings);
void				free_split(char **split);

#endif
