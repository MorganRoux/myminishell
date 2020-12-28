/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:47:03 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/28 17:26:16 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         cnt_com_parts(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int         check_nl(char *cmds) //chen if -n in cmds
{
	int		i;
	int		nl;

	nl = 0;
	i = 0;
	if (cmds[i] == '-')
	{
		i++;
		while (cmds[i])
		{
			if (cmds[i] == 'n')
				nl = 1;
			else
				return (0);
			i++;
		}
	}
	return (nl);
}

void		com_echo(t_command *mimi, char **cmds)
{
	int		argc; //ammount of cmds
	int		i;
	int		k;

	i = 0;
	argc = cnt_com_parts(cmds);
	if (argc > 1)
	{
		k = 1;
		while (cmds[k] && check_nl(cmds[k]) > 0)
			k++; //cnt ammount of -n in line
		i += k; //can be even more then 1 - we don't give a shit
		if (k == 1)
		{
            while (cmds[i]) //here we take a message after all the -n
            {
                ft_putstr_fd(cmds[i], 1);
                if (i < argc && cmds[i + 1]) //if there is still any arg to read - we put spc
                    ft_putstr_fd(" ", STDOUT_FILENO);
                // STDERR_FILENO
                // File number of stderr; 2.
                // STDIN_FILENO
                // File number of stdin; 0.
                // STDOUT_FILENO
                // File number of stdout; 1.
                i++;
            }
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else
			while (cmds[i]) //here we take a message after all the -n
            {
				ft_putstr_fd(cmds[i], 1);
				if (i < argc && cmds[i + 1]) //if there is still any arg to read - we put spc
                	ft_putstr_fd(" ", STDOUT_FILENO);
				i++;
			}
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
	mimi->ret = 0; //if there is no err
}

