/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/06 17:58:02 by cpireyre         ###   ########.fr       */
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

# define ANT_DISPLAY "\e[47m\033[30m🐜 "

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
	t_list			*path_lengths;
}					t_lemin;

typedef struct		s_edge
{
	int				flow;
	int				source;
	int				sink;
	struct s_edge	*rev;
}					t_edge;

typedef struct		s_sender
{
	int				*ants_to_send;
	int				ants_sent;
	int				ants_arrived;
	int				*ants_position;
	int				*path_lengths;
	int				shortest;
	int				real_flow;
	t_list			*queue;
}					t_sender;

typedef struct		s_trajectory
{
	t_edge			*direction;
	int				sender_id;
}					t_trajectory;

/*
**	parse.c
*/

void				store_rooms(t_list **head, t_lemin *lemin);
t_bool				store_special_rooms(t_lemin *lemin, char *name, t_byte t);

/*
**	print.c
*/

void				print_rooms(t_rooms	*map);
void				buf_print_list(t_list *node);
void				print_ant(int i, char *name, int sent, char *display);
void				print_paths_info(t_sender *sender, int flow);
void				print_edge(t_edge *edge);

/*
**	rooms.c
*/

t_rooms				*new_room(char *name_ptr, t_byte type);
char				*get_room_name(char *input);
int					find_name_list(char *name, t_rooms *rooms);

/*
**	pipes.c
*/

t_bool				store_pipes(t_list **ptr, t_lemin *lemin);

/*
**	mem.c
*/

void				free_lemin(t_lemin *addr);
void				free_split(char **split);
void				free_rooms(t_rooms **head);
void				free_graph(t_list **graph, int size);

/*
**	count.c
*/

int					ft_size_list(t_rooms *rooms);
int					count_split(char **split);
int					count_path_length(t_listarray graph, int source, int sink);
int					*size_paths(t_listarray graph, t_lemin *lemin);
int					alternate_count(t_edge **path, int source, int sink);

/*
**	edmonds_karp.c
*/

int					edmonds_karp(t_listarray max_flow_network, t_lemin *lemin);
t_edge				**breadth_first_search(t_listarray g, int s, int t, int size);

/*
**	sender.c
*/

void				send_ants(t_listarray graph, t_lemin *lemin);
int					next_vertex_id(t_list *vertex);
int					calculate_real_flow(t_sender *sender, int flow);
char				*ft_find_room_name(t_lemin *lemin, int room_nb);

/*
**	initsender.c
*/

void				init_sender(t_sender *s, t_lemin *l, t_list **graph);
void				free_sender(t_sender *sender);

/*
**	lem_in.c
*/

void				quit_lem_in(t_list **g, t_lemin *l, const char *e, int s);
void				parse(t_list **usr_in, t_list **tmp, t_lemin *lemin);

/*
**	paths.c
*/

void				how_many_ants_to_send(t_lemin *lemin, t_sender *sender);
int					too_many_ants_sent(t_lemin *l, t_sender *s, int subtract);
int					repart_extra_ants(t_lemin *l, t_sender *s, int avg, int add);
void				clear_dumb_paths(t_sender *sender, t_list *start, int flow);
void				how_many_redux(t_list *lengths, int ants);

/*
**	graph.c
*/

t_listarray			build_graph(t_lemin *lemin);

/*
**	trajectory.c
*/

t_list				*enqueue_paths(t_sender *s, t_list *start_vtx, int flow);
int					next_trajectory(t_sender *sender);

/*
**	backwards.c
*/

int					prev_vertex_id(t_list *vertex);
int					count_back_length(t_listarray graph, int source, int sink);


/*
**	super.c
*/

void				zero_path(t_list *vertex, t_listarray graph, int sink);
int					clear_super_paths(t_listarray graph, t_list *start, int end_id);

/*
**	lem_in.c
*/

t_bool				store_ants(t_list **head, int *leminants);

/*
**	analysis.c
*/

void	print_path_analysis(t_listarray graph, t_lemin *lemin, int flow);

#endif
