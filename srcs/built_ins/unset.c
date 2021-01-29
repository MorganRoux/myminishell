/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:02:03 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:40:18 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** выводит ошибку только если аргумент включает =
** если без аргументов, то просто ничего не делает
** если много аргументов, то работает с каждым из них
** если один арг косячный (ex: unset blabla=), а другой норм, то норм арг
** отрабатывает, а косячный выдает ошибку
*/

int		env_checker(t_command *mimi, char *var)
{
	char	**sep;
	char	*varenv;
	int		k;

	k = 0;
	while (mimi->env_arr[k])
	{
		sep = split_mod(mimi->env_arr[k], "=");
		varenv = ft_strdup(sep[0]);
		arr_cleaner(sep);
		if (!strcmp(varenv, var))
		{
			strdel(&varenv);
			return (1);
		}
		strdel(&varenv);
		k++;
	}
	return (0);
}

int		undet_err_case(t_command *mimi, char *cmd)
{
	int		ret;

	ret = env_valid(cmd);
	if (ret < 0)
	{
		ft_putstr_fd("minishell: unset: \" ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" \" : not a valid identifier\n", STDERR_FILENO);
		mimi->ret = 1;
		return (1);
	}
	return (0);
}

void	com_unset_sup(int i, int argc, t_command *mimi, char **cmd)
{
	while (i < argc)
	{
		if (undet_err_case(mimi, cmd[i]) == 1)
		{
			i++;
		}
		else
		{
			if (env_checker(mimi, cmd[i]) == 1)
				del_envvar(mimi, cmd[i]);
			i++;
		}
	}
}

void	com_unset(t_command *mimi, char **cmd)
{
	int		i;
	int		argc;

	argc = cnt_com_parts(cmd);
	mimi->ret = 0;
	if (argc == 1)
		return ;
	else
	{
		i = 1;
		com_unset_sup(i, argc, mimi, cmd);
	}
}
