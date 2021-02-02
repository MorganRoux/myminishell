/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:06:08 by mroux             #+#    #+#             */
/*   Updated: 2021/02/01 12:03:19 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int		get_next_line_loop(t_fl *fl, t_command *mimi, char **line)
{
	int	ln;

	ln = 0;
	while ((ln = find_line(fl)) == -1)
	{
		*line = ft_strnjoin(*line, fl->buffer + fl->pos,
						fl->bytes_read - fl->pos);
		fl->pos = 0;
		if ((fl->bytes_read = read(fl->fd, fl->buffer, BUFFER_SIZE)) < 0)
		{
			if (fl->bytes_read == 0 && *line == NULL)
				close_mimi(mimi, 1);
			reinit(fl);
			return (fl->bytes_read);
		}
	}
	*line = ft_strnjoin(*line, fl->buffer + fl->pos, ln);
	fl->pos = (fl->pos + ln + 1 >= fl->bytes_read) ? 0 : fl->pos + ln + 1;
	return (1);
}

int		get_next_line(int fd, char **line, t_command *mimi)
{
	static t_fl		fl;

	if (init(&fl, fd, line) == 0)
		return (-1);
	if (fl.pos == 0 &&
		(fl.bytes_read = read(0, fl.buffer, BUFFER_SIZE)) <= 0)
	{
		if (fl.bytes_read == 0)
			close_mimi(mimi, 1);
		return (fl.bytes_read);
	}
	return (get_next_line_loop(&fl, mimi, line));
}
