/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:12 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/19 16:17:24 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** если просто exit без аргументов, он выходит из bash.
** если с аргументами, и число, то:
        bash-3.2$ exit 7803
        exit
        т.е. он выходит из баша и пишет exit.
** если же аргумент это буква или слово, то тогда он выдает ошибку, но выходит при этом:
        bash-3.2$ exit sff
        exit
        bash: exit: sff: numeric argument required

        bash-3.2$ exit 4 s
        exit
        bash: exit: too many arguments
        bash-3.2$ echo $?
        1
*/

void	exit_shell(t_command *mimi, int stat)
{
	if (mimi->env_arr)
		arr_cleaner(mimi->env_arr);
	if (mimi->sep_cmds)
		arr_cleaner(mimi->sep_cmds);
	if (mimi->input)
		free(mimi->input);
	if (mimi->dir_now)
		free(mimi->dir_now);
	if (mimi)
		mimi = NULL;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(stat);
}


int		arg_checker(char *str)
{
	int i;

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

void	exit_stat(t_command *mini, char *str) // to set status of exit-command
{
	if (str)
	{
		ft_putnbr_fd(ft_atoi(str), 2);
		if ((arg_checker(str) && ft_strlen(str) < 19))
		{
			mini->ret = ft_atoi(str);
		}
		else if ((arg_checker(str) && ft_strlen(str) >= 19)
			&& ((str[0] != '-' && ft_atoi(str) < 0)
			|| (str[0] == '-' && ft_atoi(str) >= 0)))
		{
			mini->ret = ft_atoi(str);
		}
		else
		{
			ft_putstr_fd("MINISHELL: exit: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(" numeric argument require\n", STDERR_FILENO);
			mini->ret = 2;
		}
	}
}

void	com_exit(t_command *mini, char **args)
{
	int i;

	i = 1;
	if (args[i] && args[i + 1])
	{
		ft_putstr_fd("MINISHELL: exit: too many argument\n", STDERR_FILENO);
		mini->ret = 1;
		return ;
	}
	exit_stat(mini, args[i]);
	arr_cleaner(args);
	//exit_shell(mini, mini->ret);
}
