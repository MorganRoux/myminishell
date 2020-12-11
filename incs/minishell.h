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
# include <stdio.h>
# include "libftprintf.h"
# include "get_next_line.h"

typedef struct	        s_command
{
	char		        *exec;
    int                 argc;
	char		        **argv;
	int			        *fd_in;
	int			        *fd_out;
    int                 *fd_err;
    struct s_command    *next;
}				        t_command;

//Parsing
t_command               *parse();
t_command               *init_cmd(t_command *prev);
char                    *check_redirs(char *str, t_command *cmd);
char                    *check_redir_in(char *str, t_command *cmd);
char                    *check_redir_out(char *str, t_command *cmd);
char                    *check_redir_err(char *str, t_command *cmd);
char                    *check_args(char *str, t_command *cmd);

//Exec
int                     exec(t_command *cmds);

//Utils
void                    print_strs(char **strs);
void                    print_cmd(t_command *cmd);
void                    print_cmds(t_command *cmd);

//List
t_command			*ft_lstnew();
void			    ft_lstadd_back(t_command **alst, t_command *new);
// void			ft_lstadd_front(t_command **alst, t_command *new);
// int				ft_lstsize(t_command *lst);
// t_command			*ft_lstlast(t_command *lst);
// void			ft_lstdelone(t_command *lst, void (*del)(void*));
// void			ft_lstclear(t_command **lst, void (*del)(void*));
// void			ft_lstiter(t_command *lst, void (*f)(void *));
// t_command			*ft_lstmap(t_command *lst, void *(*f)(void *),
// 				void (*del)(void *));
#endif
