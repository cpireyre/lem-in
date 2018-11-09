/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/09 12:33:13 by tboissel         ###   ########.fr       */
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

typedef struct		s_paths
{
	int				*scout;
	struct s_paths	*next;
	struct s_paths  *prev;
}					t_paths;

typedef struct		s_lemin
{
	char			*start_name;
	char			*end_name;
	int				ants;
	t_rooms			*rooms;
	char			**pipes;
	int				end_links;
	int				map_size;
	t_paths			*paths;
	int				*visited_rooms;
}					t_lemin;

/*
**	parse.c
*/

t_bool				store_ants(t_list **head, t_lemin *lemin);
t_bool				add_room(t_lemin **lemin, char *input, t_byte type);
void				store_rooms(t_list **head, t_lemin *lemin);
t_bool				store_special_rooms(t_lemin *lemin, char *name, t_byte t);

/*
**	print.c
*/

void				print_rooms(t_rooms	*map);
void				print_list(t_list **head);
void				print_paths(t_paths *path);

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

/*
**	count.c
*/

int					ft_size_list(t_rooms *rooms);
int					count_split(char **split);

/*
**	algo.c
*/

t_bool				algo(t_lemin *lemin);
int					get_end_links(t_lemin *lemin);
void				create_first_path(t_lemin *lemin);
t_bool				scout(t_lemin *lemin);
int					ft_get_nb_separations(t_lemin *lemin);
void				create_following_path(t_paths **path);
void				scout_progress(t_lemin *lemin, int separation);

#endif
