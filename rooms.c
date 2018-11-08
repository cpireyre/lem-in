/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 08:06:24 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/08 08:49:56 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	room_is_valid(const char *name)
{
	if (name[0] == 'L' || name[0] == '#')
		return (false);
	name += ft_strlen(name) - 1;
	while (ft_isdigit(*name))
		name--;
	name++;
	if (!ft_isint(name))
		return (false);
	name--;
	if (*name != ' ')
		return (false);
	while (ft_isdigit(*name))
		name--;
	name++;
	if (!ft_isint(name))
		return (false);
	name--;
	if (*name != ' ')
		return (false);
	return (true);
}

static t_rooms	*new_room(char *name_ptr, t_byte type)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = name_ptr;
	new->type = type;
	new->next = NULL;
	return (new);
}

static char	*get_room_name(const char *input)
{
	if (room_is_valid(input))
	{
		if (DEBUG)
			ft_printf("DEBUG: Room \"%s\" sounds OK.\n", input);
		return (ft_strdup(input));
	}
	else
	{
		if (DEBUG)
			ft_printf("DEBUG: \"%s\" is not a valid room name.\n", input);
		return (NULL);
	}
}

t_bool	add_room(t_rooms **map, char *input, t_byte type)
{
	t_rooms *new;
	char	*room_name;

	room_name = get_room_name(input);
	if (!room_name)
	{
		ft_strdel(&room_name);
		return (false);
	}
	new = new_room(room_name, type);
	new->next = *map;
	*map = new;
	return (true);
}

