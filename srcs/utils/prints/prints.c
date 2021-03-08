/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:33:37 by mroux             #+#    #+#             */
/*   Updated: 2021/03/08 20:33:39 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strs(char **strs)
{
	while (*strs != NULL)
	{
		ft_printf(":%s:\n", *strs);
		strs++;
	}
}

void	print_lst_str(t_list_str *strs)
{
	while (strs != NULL)
	{
		ft_printf(":%s:\n", strs->content);
		strs = strs->next;
	}
}

void	print_cmd_sup(t_command *cmd, int *i, t_list_str *lst)
{
	ft_printf("\n-----\nExec:%s:\n", cmd->exec);
	*i = 0;
	lst = cmd->args;
	while (lst != 0)
	{
		ft_printf("Arg%d:%s:\n", *i, lst->content);
		lst = lst->next;
		(*i)++;
	}
	*i = 0;
	lst = cmd->files_in;
	while (lst != 0)
	{
		ft_printf("Fdin%d:%s:\n", *i, lst->content);
		lst = lst->next;
		(*i)++;
	}
	*i = 0;
	lst = cmd->files_out;
	while (lst != 0)
	{
		ft_printf("Fdout%d:%s:\n", *i, lst->content);
		lst = lst->next;
		(*i)++;
	}
}

void	print_cmd(t_command *cmd)
{
	int			i;
	t_list_str	*lst;

	if (cmd == NULL)
		return ;
	lst = NULL;
	print_cmd_sup(cmd, &i, lst);
	i = 0;
	lst = cmd->files_append;
	while (lst != 0)
	{
		ft_printf("Fdappend%d:%s:\n", i, lst->content);
		lst = lst->next;
		i++;
	}
	if (cmd->pipe != 0)
		ft_printf("Pipe\n");
	ft_printf("-----\n");
}

void	print_cmds(t_list_cmd *cmd)
{
	while (cmd != NULL)
	{
		print_cmd(cmd->content);
		cmd = cmd->next;
	}
}
