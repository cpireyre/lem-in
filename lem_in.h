/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:41:25 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/06 13:42:30 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define CONNECTED 4
# define START 2
# define END 3
# define NORMAL 1

typedef struct		s_rooms
{
	char			*room_name;
	t_byte			typeroom;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_lemin
{
	int				ants;
	t_rooms			*rooms;
	int				**pipes;
}					t_lemin;

t_bool				store_ants(t_list **head, t_lemin *lemin);
void				print_list(t_list **head);

#endif
