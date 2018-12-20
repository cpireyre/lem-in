/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:13:37 by cpireyre          #+#    #+#             */
/*   Updated: 2018/06/23 09:53:01 by cpireyre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUF_H
# define BUF_H

# include <unistd.h>
# include <wchar.h>

# define BUFF_SIZE		32768

typedef struct		s_buf
{
	char	tab[BUFF_SIZE];
	size_t	pos;
	int		filedesc;
	int		written;
}					t_buf;

void				flush_buf(t_buf *buf);
void				putc_buf(t_buf *buf, char c);
void				putstr_buf(t_buf *buf, char *str);
void				repeat_buf(t_buf *buf, char c, int num);
void				putnstr_buf(t_buf *buf, char *str, int n);
void				putc_buf_unicode(t_buf *buf, wchar_t uchar);
void				putstr_buf_unicode(t_buf *buf, wchar_t *ustr);
void				putnstr_buf_unicode(t_buf *buf, wchar_t *ustr, int n);

#endif
