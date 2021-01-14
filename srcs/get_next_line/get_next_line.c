/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:06:08 by mroux             #+#    #+#             */
/*   Updated: 2021/01/13 14:56:49 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include "minishell.h"
#include <stdio.h>

int		get_next_line(int fd, char **line, t_command *mimi)
{
	static t_fl		fl;
	int				ln;

	ln = 0;
	mimi->args = NULL;
	if (init(&fl, fd, line) == 0)
		return (-1);
	if (fl.pos == 0 &&
		(fl.bytes_read = read(0, fl.buffer, BUFFER_SIZE)) <= 0) //changed for 0 because we will not have a file desc
		return (fl.bytes_read);
	// if (fl.bytes_read == 0)
	// {
	// 	ft_putstr_fd(strerror(errno), 2);
	// 	close_mimi(mimi, 1);
	// }
	while ((ln = find_line(&fl)) == -1)
	{
		*line = ft_strnjoin(*line, fl.buffer + fl.pos, fl.bytes_read - fl.pos);
		fl.pos = 0;
		if ((fl.bytes_read = read(fl.fd, fl.buffer, BUFFER_SIZE)) <= 0)
		{
			reinit(&fl);
			return (fl.bytes_read);
		}
	}
	// if (fl.bytes_read < 1)
	// {
	// 	ft_putstr_fd(strerror(errno), 2);
	// 	close_mimi(mimi, 1);
	// }
	*line = ft_strnjoin(*line, fl.buffer + fl.pos, ln);
	fl.pos = (fl.pos + ln + 1 >= fl.bytes_read) ? 0 : fl.pos + ln + 1;
	return (1);
}
