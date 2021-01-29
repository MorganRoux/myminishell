/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:06:08 by mroux             #+#    #+#             */
/*   Updated: 2021/01/29 14:43:34 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int		get_next_line(int fd, char **line, t_command *mimi)
{
	static t_fl		fl;
	int				ln;

	ln = 0;
	if (init(&fl, fd, line) == 0)
		return (-1);
	if (fl.pos == 0 &&
		(fl.bytes_read = read(0, fl.buffer, BUFFER_SIZE)) <= 0)
	{
		if (fl.bytes_read == 0)
			close_mimi(mimi, 1);
		return (fl.bytes_read);
	}
	while ((ln = find_line(&fl)) == -1)
	{
		*line = ft_strnjoin(*line, fl.buffer + fl.pos, fl.bytes_read - fl.pos);
		fl.pos = 0;
		if ((fl.bytes_read = read(fl.fd, fl.buffer, BUFFER_SIZE)) < 0)
		{
			if (fl.bytes_read == 0 && *line == NULL)
				close_mimi(mimi, 1);
			reinit(&fl);
			return (fl.bytes_read);
		}
	}
	*line = ft_strnjoin(*line, fl.buffer + fl.pos, ln);
	fl.pos = (fl.pos + ln + 1 >= fl.bytes_read) ? 0 : fl.pos + ln + 1;
	return (1);
}
