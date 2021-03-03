/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:48:33 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:21:45 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	prompt(void)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("erreur de détermination du répertoire actuel", 2);
		return ;
	}
	ft_putstr_fd(cwd, 2);
	ft_putstr_fd(" $ ", 2);
	free(cwd);
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
	signal_callback();
	while (i != 0)
	{
		prompt();
		signal_callback();
		if ((i = get_next_line(0, &line)) == 0)
			break ;
		exec_loop(line);
		free(line);
	}
	free(line);
	ft_putstr_fd("exit\n", 2);
	if (g_globstruct.ret == 0)
		return (0);
	errno = g_globstruct.ret;
	return (errno);
}
