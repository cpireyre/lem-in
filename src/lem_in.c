/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:41:08 by cpireyre          #+#    #+#             */
/*   Updated: 2018/12/09 11:47:07 by tboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	quit_lem_in(t_list **lst, t_lemin *env, const char *err, int status)
{
	ft_lstdel(lst, &ft_free_node);
	free_lemin(env);
	ft_exit(err, status);
}

t_bool				store_ants(t_list **head, int *leminants)
{
	while (((char*)(*head)->content)[0] == '#')
	{
		if (ft_strequ((char*)(*head)->content, "##start")
				|| ft_strequ((char*)(*head)->content, "##end"))
			return (false);
		(*head) = (*head)->next;
	}
	if (ft_isint((char*)(*head)->content))
	{
		*leminants = ft_atoi((char*)(*head)->content);
		if (DEBUG > 1)
			ft_printf("DEBUG: Stored %d ant%c.\n", *leminants, \
					*leminants > 1 ? 's' : 0);
		if (*leminants >= 0)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

static t_bool	map_has_in_out(t_lemin *lemin)
{
	if (DEBUG > 1)
		ft_printf("DEBUG: Start room: \"%s\", end room: \"%s\".\n",
				lemin->start_name, lemin->end_name);
	return (lemin->start_name && lemin->end_name);
}

t_list	*stdin_to_list(void)
{
	t_list		*usr_in;
	char		*l;

	l = NULL;
	usr_in = NULL;
	while (ft_gnl(0, &l))
		ft_lstappend(&usr_in, ft_lstnew(l, sizeof(char) * (ft_strlen(l) + 1)));
	return (usr_in);
}

void	parse(t_list **usr_in, t_list **tmp, t_lemin *lemin)
{
	if (!(*usr_in))
		quit_lem_in(tmp, lemin, "ERROR: No arguments.\n", EXIT_FAILURE);
	if (!(store_ants(usr_in, &lemin->ants)))
		quit_lem_in(tmp, lemin, "ERROR: Invalid number of ants.\n", EXIT_FAILURE);
	*usr_in = (*usr_in)->next;
	store_rooms(usr_in, lemin);
	if (!lemin->rooms || !map_has_in_out(lemin))
		quit_lem_in(tmp, lemin, "ERROR: Map error.\n", EXIT_FAILURE);
	if (DEBUG > 1)
	{
		print_rooms(lemin->rooms);
		ft_printf("DEBUG: All rooms are stored. Processing pipes.\n");
	}
	if (!store_pipes(usr_in, lemin))
		quit_lem_in(tmp, lemin, "ERROR: No pipes.\n", EXIT_FAILURE);
}
