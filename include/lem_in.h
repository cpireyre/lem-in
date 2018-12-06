/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/06 14:07:23 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdlib.h>
# include <mlx.h>
# include <unistd.h>

/*
**	Debug settings:
**		0: no debug
**		1: stuff that's relevant right now
**		2: more stuff, some of it not so important anymore
**		3 and up: much more than you wanted to know
*/

# define DEBUG		0

# define CONNECTED	4
# define START		2
# define END		3
# define NORMAL		1

# if defined(__APPLE__) && defined(__MACH__)
#  define ANT_DISPLAY "\x1b[47m\x1b[30m🐜 "
# else
#  define ANT_DISPLAY "\033[47m\033[30m🐜 "
# endif
# define W			0xFFFFFF
# define REGULAR	true
# define BACKWARDS	false

typedef struct			s_image
{
	void				*img_ptr;
	int					*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_image;

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct		s_rooms
{
	int				ant_nb;
	char			*name;
	t_coord			coord;
	t_byte			type;
	struct s_rooms	*next;
}					t_rooms;

typedef struct			s_minilibx
{
	int					w_height;
	int					w_width;
	void				*m_ptr;
	void				*w;
	t_image				img;
}						t_minilibx;

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
	t_list			*usr_in;
}					t_lemin;

typedef struct		s_visu
{
	t_lemin 		*lemin;
	t_list			*reset_usr_in;
	int				*ants_pos_v;
	t_bool			tuto;
	t_bool			room_name;
	t_bool			auto_mode;
	t_byte			mv_done;
	t_minilibx		*mlx;
	time_t			time;
}					t_visu;

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

/*
**	parse.c
*/

t_bool				store_ants(t_list **head, t_lemin *lemin);
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
t_rooms				*new_room(char *name_ptr, t_byte type, t_coord *coord, t_lemin *lemin);
char				*get_room_name(char *input);

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

/*
**	count.c
*/

int					ft_size_list(t_rooms *rooms);
int					count_split(char **split);
int					count_path_length(t_list **graph, int source, int sink);
void				clear_dumb_paths(t_sender *sender, t_list *start, int flow);

/*
**	edmonds_karp.c
*/

int					edmonds_karp(t_list ***max_flow_network, t_lemin *lemin);
t_edge				**breadth_first_search(t_list **graph, int source, int sink, int size);

/*
**	sender.c
*/

void				send_ants(t_list **graph, t_lemin *lemin);
int					next_vertex_id(t_list *vertex);
int					calculate_real_flow(t_sender *sender, int flow);
char				*ft_find_room_name(t_lemin *lemin, int room_nb);

/*
**	lem_in.c
*/

void				quit_lem_in(t_list **lst, t_lemin *env, const char *err, int status);
void				parse(t_list **usr_in, t_list **tmp, t_lemin *lemin);

/*
**	traverse.c
*/

void				link_graph(t_list ***graph, int source, int sink, t_lemin *lemin);

/*
**	splitcheck.c
*/

int					shortest_path_length(t_list ***graph, int source, int sink, int size);
int					alternate_count(t_edge **path, int source, int sink);

/*
**	paths.c
*/

int					*size_paths(t_list **graph, t_lemin *lemin);
void				how_many_ants_to_send(t_lemin *lemin, t_sender *sender);
int					too_many_ants_sent(t_lemin *lemin, t_sender *sender, int ants_to_substract);
int					repart_extra_ants(t_lemin *lemin, t_sender *sender, int average, int ants_to_add);

/*
**	visu
*/

void				parse_visu(t_list **usr_in, t_lemin *visu);
void				visu(t_lemin *visu);
void				ft_init_mlx(t_visu *visu);
int					key_events(int key, t_visu *visu);
int					exit_visu(t_visu *visu);
void				ft_create_image(t_visu *visu);
void				ft_draw_point(t_coord point, t_visu *lemin);
void				ft_bresenham(t_coord p1, t_coord p2, t_visu *visu);
void				create_pipes(t_visu *visu);
void				ft_background(t_visu *visu);
void				add_ant(t_visu *visu, char *line);
int					get_room_id(t_rooms *rooms, char *room_name);
void				ft_tutorial(t_visu *visu);
void				ft_room_name(t_visu *visu);
void				ft_move_ants(t_visu *visu, t_bool mode);
t_bool				test_mv_ants(t_visu *visu, time_t time_now);
int					rand_a_b(int a, int b);
void				display_ant_nb(t_visu *visu);
int					ft_loop_events(t_visu *visu);
void				empty_rooms(t_visu *visu);
/*
**	graph.h
*/

t_list				**build_graph(t_lemin *lemin);
void				free_graph(t_list **graph, int size);

/*
**	trajectory.c
*/

t_list				*queue_paths(t_sender *sender, t_list *start_vtx, int flow);
int					next_trajectory(t_sender *sender);

/*
**	main.c
*/

t_list				*stdin_to_list(void);

#endif
