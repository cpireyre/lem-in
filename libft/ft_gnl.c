/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 10:20:41 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/21 12:17:06 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_cat(char **gnl, char *tmp)
{
	size_t	combined_size;

	if (!tmp || !(*tmp))
		return ;
	combined_size = 0;
	if (gnl && *gnl)
		combined_size += ft_strlen(*gnl);
	combined_size += ft_strlen(tmp);
	*gnl = ft_strrealloc(*gnl, combined_size);
	*gnl = ft_strcat(*gnl, tmp);
}

static void	get_one_line(char **gnl, char **line)
{
	int		split;
	char	*tmp;

	if (!gnl)
		return ;
	split = ft_strclen(*gnl, SPLIT);
	if (split != -1)
	{
		*(*gnl + split) = 0;
		*line = ft_strdup(*gnl);
		tmp = *gnl;
		*gnl = ft_strdup(tmp + split + 1);
		ft_strdel(&tmp);
	}
	else
	{
		*line = ft_strdup(*gnl);
		ft_strdel(gnl);
	}
}

int			ft_gnl(const int fd, char **line)
{
	static char		*gnl[OPEN_MAX];
	char			buf[GNL_BUFF + 1];
	int				ret;

	if (!line || fd < 0)
		return (-1);
	if (*line)
		ft_strdel(line);
	while ((ret = read(fd, buf, GNL_BUFF)) || (gnl[fd] && *(gnl[fd])))
	{
		if (ret < 0 || (buf[ret] = 0))
			return (-1);
		if (buf[0])
			free_cat(&gnl[fd], buf);
		if (gnl[fd] && *(gnl[fd]) && (ft_strchr(gnl[fd], SPLIT)
					|| ret < GNL_BUFF))
		{
			get_one_line(&(gnl[fd]), line);
			return (1);
		}
	}
	ft_strdel(&gnl[fd]);
	return (0);
}
