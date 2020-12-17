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

typedef t_list          t_list_str;
typedef t_list          t_list_cmd;

typedef struct	        s_command
{
	char		        *exec;
	t_list_str		    *args;
	int			        *fd_in;
	int			        *fd_out;
    int                 *fd_err;
}				        t_command;



//Parsing
t_list_cmd              *parse();
t_list_str              *split_tokens(char *line);

//Exec
int                     exec(t_list_cmd *cmds);

//Utils
void                    print_strs(char **strs);
void                    print_lst_str(t_list_str *strs);
void                    print_cmd(t_command *cmd);
void                    print_cmds(t_list_cmd *cmd);
int                     is_meta_char(char c);
int                     is_meta_str(char *str);

//List
t_list_cmd              *ft_lstinit();
t_list                  *ft_lstof(t_list *lst, int index);
// t_command			*ft_lstnew();
// void			    ft_lstadd_back(t_command **alst, t_command *new);
// void			ft_lstadd_front(t_command **alst, t_command *new);
// int				ft_lstsize(t_command *lst);
// t_command			*ft_lstlast(t_command *lst);
// void			ft_lstdelone(t_command *lst, void (*del)(void*));
// void			ft_lstclear(t_command **lst, void (*del)(void*));
// void			ft_lstiter(t_command *lst, void (*f)(void *));
// t_command			*ft_lstmap(t_command *lst, void *(*f)(void *),
// 				void (*del)(void *));
#endif
