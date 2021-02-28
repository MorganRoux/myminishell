/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:16 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:36:57 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** export без аргументов, то он просто выводит список всех переменных
**		окружения, с приставкой declare -x, а еще он сортирует список
**		в алфавитном порядке, например:
** ```bash
** declare -x COLORFGBG="15"
** declare -x COLORTERM="truecolor"
** declare -x COMMAND_MODE="unix2003"
** declare -x HOME="/Users/annaleonova"
** ```
**
** export с аргументом без '=', то он просто печатает ее
** export без ключа, но со знаком = добавляет переменную в переменные
**		окружения! при этом после знака = буду двойные кавычки.
**		например, x= будет в списке.
** export по ключу, который уже существует, меняет значение этого ключа.
** если export аргумент (без равно), то он не добавляет это в переменные
**		окружения (то есть в env_arr этой переменной нет), но при этом
**
** export ZSH=/Users/dbliss/.oh-my-zsh
** export USER=dbliss
** export PWD=
** export OLDPWD (вот это не должно заноситься в env_arr, либо в конце ее
** удалить надо (или лучше просто не отображать в функции env_arr!
**		типо распечатал и удалил из массива.)
** ```bash
** declare -x ZSH="/Users/dbliss/.oh-my-zsh"
** declare -x USER="dbliss"
** declare -x PWD=""
** declare -x OLDPWD
** ```
*/

int		exp_err_case(t_command *mimi, char *cmd)
{
	int		ret;

	ret = env_valid(cmd);
	if (ret < 0)
	{
		ft_putstr_fd("MINISHELL: export: \" ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" \" : not a valid identifier\n", STDERR_FILENO);
		mimi->ret = 1;
		return (1);
	}
	return (0);
}

/*
** in case of export of "addition value"
** ex:
** bash-3.2$ export ok=v1
** bash-3.2$ export ok+=v2
** bash-3.2$ echo $ok
** SO HERE IN THE END OUR ok = v1v2
*/

int		c_exp_sup2(t_command *mimi, char **cmd, int k)
{
	if (mimi->ch == 1)
	{
		upd_newenv2(mimi, cmd[k]);
		mimi->ch = 0;
		return (1);
	}
	return (0);
}

void	c_exp_sup3(t_command *mimi, char **cmd, int *k, int *len)
{
	int		i;
	char	*tmp;

	i = 0;
	*len = ft_strlen(cmd[*k]);
	tmp = cmd[*k];
	if (cmd[*k][*len - 1] == '=')
	{
		while (cmd[*k][i])
		{
			if (cmd[*k][i - 1] == '+' && cmd[*k][i] == '=')
				(*k)++;
			i++;
		}
		tmp = ft_strjoin(tmp, cmd[*k]);
		mimi->ch = 3;
	}
	if (mimi->ch == 3)
	{
		upd_newenv(mimi, tmp);
		mimi->ch = 0;
	}
	else
		upd_newenv(mimi, cmd[*k]);
}

void	c_exp_sup(t_command *mimi, char **cmd, int k, int len)
{
	int		argc;

	argc = cnt_com_parts(cmd);
	while (k < argc)
	{
		if (exp_err_case(mimi, cmd[k]) == 1)
			k++;
		else
		{
			if (val_adder(cmd[k]) > 0)
				c_exp_sup3(mimi, cmd, &k, &len);
			else
			{
				if (c_exp_sup2(mimi, cmd, k) == 0)
				{
					if (mimi->ch != 2)
						envvar_update(mimi, ft_strdup(cmd[k]));
				}
				len = ft_strlen(cmd[k]);
				if (cmd[k][len - 1] == '=')
					mimi->ch = 1;
			}
			k++;
		}
	}
}

void	com_export(t_command *mimi, char **cmd)
{
	int		k;
	int		argc;
	int		len;

	len = 0;
	k = 1;
	argc = cnt_com_parts(cmd);
	mimi->ret = 0;
	if (argc == 1)
		envvar_pr_sort(mimi);
	else
		c_exp_sup(mimi, cmd, k, len);
}
