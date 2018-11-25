/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/25 16:21:28 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>

/*
**	Debug settings:
**		0: no debug
**		1: stuff that's relevant right now
**		2: more stuff, some of it not so important anymore
**		3 and up: much more than you wanted to know
*/

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
	int				start_id;
	int				end_id;
	int				map_size;
	char			*start_name;
	char			*end_name;
	int				ants;
	t_rooms			*rooms;
	char			**pipes;
	int				flow;
	char			*ant_display;
}					t_lemin;

typedef struct		s_edge
{
	int				flow;
	int				source;
	int				sink;
	struct s_edge	*rev;
	struct s_edge	*next;
	struct s_edge	*previous;
}					t_edge;

typedef struct		s_sender
{
	int				*ants_to_send;
	int				ants_sent;
	int				ants_arrived;
	int				*ants_position;
	int				switch_path;
	int				*path_lengths;
	int				shortest;
	int				to_skip;
	int				real_flow;
}					t_sender;

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
void				buf_print_list(t_list *node);
void				print_ant(int i, char *room_name, int ants_sent, char *display);
void				print_paths_info(t_sender *sender, int flow);

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

t_bool				store_pipes(t_list **ptr, t_lemin *lemin);

/*
**	mem.c
*/

void				free_lemin(t_lemin *addr);
void				free_string(void *string, size_t size);
void				free_split(char **split);
void				free_node(void *ptr, size_t size);
void				free_rooms(t_rooms **head);

/*
**	count.c
*/

int					ft_size_list(t_rooms *rooms);
int					count_split(char **split);

/*
**	edmonds_karp.c
*/

int					edmonds_karp(t_list ***max_flow_network, t_lemin *lemin);
t_edge				**breadth_first_search(t_list **graph, int source, int sink, int size);

/*
**	sender.c
*/

t_bool				send_one_ant(t_list *vertex, t_lemin *lemin, int i, t_sender *sender);
void				send_ants(t_list **graph, t_lemin *lemin);
int					next_vertex_id(t_list *vertex);
int					calculate_real_flow(t_sender *sender, int flow);

/*
**	lem_in.c
*/

void				quit_lem_in(t_list **lst, t_lemin *env, const char *err, int status);
t_bool				map_has_in_out(t_lemin *lemin);
t_list				*stdin_to_list(void);
void				parse(t_list **usr_in, t_list **tmp, t_lemin *lemin);

/*
**	traverse.c
*/

void				link_graph(t_list ***graph, int source, int sink);

/*
**	splitcheck.c
*/

int					shortest_path_length(t_list ***graph, int source, int sink, int size);
int					alternate_count(t_edge **path, int source, int sink);
int					count_path_length(t_list **graph, int source, int sink);
void				clear_dumb_paths(t_sender *sender, t_list *start, int flow);

/*
**	paths.c
*/

int					*size_paths(t_list **graph, t_lemin *lemin);
int					ft_array_min(int *array, int size);
void				how_many_ants_to_send(t_lemin *lemin, t_sender *sender);
int					too_many_ants_sent(t_lemin *lemin, t_sender *sender, int ants_to_substract);
int					repart_extra_ants(t_lemin *lemin, t_sender *sender, int average, int ants_to_add);
int					get_optimal_path(t_sender *sender, t_list *starting_edges, int flow);

/*
**	graph.h
*/

void				fill_edge(t_edge *edge, int source, int sink);
void				add_connections_to_graph(t_list **vertex, int vertex_nbr, char *connections);
t_list				**build_graph(t_lemin *lemin);
void				free_edge(void *ptr, size_t size);
void				free_graph(t_list **graph, int size);

#endif
