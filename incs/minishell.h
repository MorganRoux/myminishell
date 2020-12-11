/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:35:37 by mroux             #+#    #+#             */
/*   Updated: 2019/11/14 19:27:48 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_command
{
	char		*cmd;
    int         *argc;
	char		**argv;
	int			*fd_in;
	int			*fd_out;
    int         *fd_err;
    t_command   *next;
}				t_command;

t_command       *parse();
t_command       *init_command(char *command);
#endif
