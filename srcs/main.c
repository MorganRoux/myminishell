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

void	env_filling(char **envp, t_command *mimi)
{
	int			i;
	int			len;

	i = 0;
	len = get_strs_len(envp);
	mimi->env_arr = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!(mimi->env_arr))
	{
		ft_printf("exit");
		exit(1);
	}
	while (envp[i])
	{
		mimi->env_arr[i] = ft_strdup(envp[i]);
		if (!(mimi->env_arr))
		{
			ft_printf("exit");
			exit(1);
		}
		i++;
	}
}

void	prompt()
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
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
	ft_bzero(&g_globstruct, sizeof(t_command));
	env_filling(envp, &g_globstruct);
	signal_callback();
	while (i != 0)
	{
		prompt();
		signal_callback();
		if ((i = get_next_line(0, &line, &g_globstruct)) == 0)
			break ;
		exec_loop(line, &g_globstruct);
		free(line);
	}
	free(line);
	ft_printf("exit\n");
    if (g_globstruct.ret == 0)
        return (0);
    errno = g_globstruct.ret;
	return (errno);
}
