/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:48:33 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/14 16:00:23 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_command	g_globstruct;

void	env_filling(char **envp, t_command *mimi)
{
	int			i;
	int			len;

	i = 0;
	len = cnt_com_parts(envp);
	mimi->env_arr = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!(mimi->env_arr))
		close_mimi(mimi, 1);
	while (envp[i])
	{
		mimi->env_arr[i] = ft_strdup(envp[i]);
		if (!(mimi->env_arr))
			close_mimi(mimi, 1);
		i++;
	}
}

/*
** update cwd in the structure
*/

void	upd_cwd(t_command *mimi, char *cwd)
{
	if (mimi->dir_now)
		free(mimi->dir_now);
	mimi->dir_now = ft_strdup(cwd);
}

/*
** /Users/alina9012/Desktop/folder_now $ // or we can leave just a $
*/

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

/*
** Salut! Ca va ?:)  
** I delete initialisation of t_command g_globstruct variable from main
** because it creates a conflictst with the eponymous variable
** in the beginnign of the file. I need it exactly here - otherwise
** it will not connect to our structure and I will not be able to manage
** exit codes of the signals needed.
** Have a great day !
*/

int		main(int argc, char *argv[], char *envp[])  
{
	char		*line;
	t_list_cmd	*cmds;
	int			i;

	(void)argc;
	(void)argv;
	line = NULL;
	i = 1;
	ft_bzero(&g_globstruct, sizeof(t_command));
	env_filling(envp, &g_globstruct);
	sig_manag();
	ft_printf("Minishell (alkanaev & mroux). Welcome ! :>\n");
	while (i != 0)
	{
		sig_manag();
		prompt(&g_globstruct);
		if ((i = get_next_line(0, &line, &g_globstruct)) == -1)
			break;
		if (!((cmds = parse(line, &g_globstruct)) == NULL))
		    exec(&g_globstruct, cmds);
        free_cmds(cmds);
        free(line);
	}
    return (0);
}
