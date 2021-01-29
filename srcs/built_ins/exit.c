/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:12 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:13:12 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** если просто exit без аргументов, он выходит из bash.
** если с аргументами, и число, то:
**        bash-3.2$ exit 7803
**        exit
**        т.е. он выходит из баша и пишет exit.
** если же аргумент это буква или слово, то тогда он выдает ошибку, но
**	выходит при этом:
**        bash-3.2$ exit sff
**        exit
**        bash: exit: sff: numeric argument required
**
**        bash-3.2$ exit 4 s
**        exit
**        bash: exit: too many arguments
**        bash-3.2$ echo $?
**        1
*/

void	close_mimi(t_command *mimi, int ret)
{
	if (mimi->env_arr)
		arr_cleaner(mimi->env_arr);
	if (mimi->dir_now)
		free(mimi->dir_now);
	if (mimi)
		mimi = NULL;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(ret);
}

int		arg_checker(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || (str[i] == '-') || (str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

/*
** part of com_exit to set status of exit-command
** 19 - max len of exit code, we protect from overflow
*/

void	com_exit_sup(t_command *mimi, char *str)
{
	if (str)
	{
		ft_putnbr_fd(ft_atoi(str), 2);
		if ((arg_checker(str) && ft_strlen(str) < 19))
			mimi->ret = ft_atoi(str);
		else if ((arg_checker(str) && ft_strlen(str) >= 19)
			&& ((str[0] != '-' && ft_atoi(str) < 0)
			|| (str[0] == '-' && ft_atoi(str) >= 0)))
			mimi->ret = ft_atoi(str);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(" numeric argument require\n", STDERR_FILENO);
			mimi->ret = 2;
		}
	}
}

void	com_exit(t_command *mimi, char **args)
{
	int i;

	i = 1;
	if (args[i] && args[i + 1])
	{
		ft_putstr_fd("mimishell: exit: too many argument\n", STDERR_FILENO);
		mimi->ret = 1;
		return ;
	}
	com_exit_sup(mimi, args[i]);
	arr_cleaner(args);
	close_mimi(mimi, mimi->ret);
}
