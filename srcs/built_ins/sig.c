/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:58:37 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/01 12:20:24 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_command	g_globstruct;

void		sig_ctrlc(int signal)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (!(g_globstruct.pid))
		prompt(&g_globstruct);
	else
	{
		prompt(&g_globstruct);
		kill(g_globstruct.pid, signal);
	}
	g_globstruct.ret = 130;
}

void		sig_ctrlbs(int signal)
{
	if (g_globstruct.pid)
	{
		kill(g_globstruct.pid, signal);
		g_globstruct.ret = 131;
		ft_putstr_fd("\nquit (core dumped)\n", STDERR_FILENO);
	}
}

void		sig_manag(void)
{
	if (signal(SIGINT, &sig_ctrlc) == SIG_ERR)
		ft_putstr_fd("SIGINT error", STDOUT_FILENO);
	if (signal(SIGQUIT, &sig_ctrlbs) == SIG_ERR)
		ft_putstr_fd("SIGQUIT error", STDOUT_FILENO);
}
