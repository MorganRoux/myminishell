/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:48:33 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/02 16:47:11 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_command	g_globstruct;

/*
** update cwd in the structure
*/

void	upd_cwd(t_command *mimi, char *cwd)
{
	if (mimi->dir_now)
		free(mimi->dir_now);
	mimi->dir_now = ft_strdup(cwd);
}

void	prompt(t_command *mimi)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && mimi->dir_now)
		cwd = ft_strdup(mimi->dir_now);
	ft_putstr_fd(cwd, 2);
	ft_putstr_fd(" $ ", 2);
	upd_cwd(mimi, cwd);
	strdel(&cwd);
}

int		main(int argc, char *argv[], char *envp[])
{
	char		*line;
	int			i;

	(void)argc;
	(void)argv;
	line = NULL;
	i = 1;
	init_globals(envp);
	signal(SIGQUIT, &signal_callback);
	signal(SIGINT, &signal_callback);
	while (i != 0)
	{
		ft_printf("$ ");//prompt(&g_globstruct);
		if ((i = get_next_line(0, &line, &g_globstruct)) == -1)
			break ;
		exec_loop(line, &g_globstruct);
		free(line);
	}
	return (0);
}
