/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:33:30 by cpireyre          #+#    #+#             */
/*   Updated: 2018/11/24 17:04:14 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# if defined(__APPLE__) && defined(__MACH__)
#  include <sys/syslimits.h>
# else
#  define OPEN_MAX 10240
# endif

# define GNL_BUFF	1
# define SPLIT		'\n'
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int					get_next_line(const int fd, char **line);

#endif
