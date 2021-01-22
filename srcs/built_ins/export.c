/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:16 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/22 14:03:07 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

int		env_valid(char *env_arr)
{
	int		i;
	int		len;
	char	**sep;

	i = 0;
	if (env_arr[0] == '\0' || space_checker(env_arr) == 1)
		return (-1);
	if (ft_isdigit(env_arr[0]) == 1)
		return (-2);
	if (env_arr[0] == '=')
		return (-3);
	sep = split_mod(env_arr, "=");
	len = ft_strlen(sep[0]);
	while (sep[0][i])
	{
		if (ft_itsokay(sep[0][i]) == 0 && sep[0][len - 1] != '+')
		{
			arr_cleaner(sep);
			return (-4);
		}
		i++;
	}
	arr_cleaner(sep);
	return (1);
}

void	upd_newenv2_sup(t_command *mimi, char **tmp, int j)
{
	char	**sep2;
	char	*var2;
	char	*val2;
	char	*new_env2;
	int		ret2;

	sep2 = split_mod(tmp[j - 1], "+=");
	var2 = ft_strdup(sep2[0]);
	val2 = ft_strdup(sep2[1]);
	arr_cleaner(sep2);
	ret2 = ind_of_envvar(mimi, var2);
	if (ret2 < 0)
		new_env2 = join_mod(var2, "=", val2);
	else
		new_env2 = ft_strjoin(mimi->env_arr[ret2], val2);
	envvar_update(mimi, new_env2);
	strdel(&var2);
}

void	upd_newenv2(t_command *mimi, char *env_upd)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	del_envvar(mimi, env_upd);
	len = cnt_com_parts(mimi->env_arr);
	tmp = (char **)ft_calloc(sizeof(char *), len + 2);
	if (tmp == NULL)
		return ;
	while (mimi->env_arr[i])
	{
		tmp[j] = ft_strdup(mimi->env_arr[i]);
		i++;
		j++;
	}
	if (mimi->ch == 1)
	{
		tmp[j - 1] = ft_strjoin(tmp[j - 1], ft_strdup(env_upd));
		mimi->ch = 2;
	}
	upd_newenv2_sup(mimi, tmp, j);
}

void	upd_newenv(t_command *mimi, char *env_upd)
{
	char	**sep;
	char	*var;
	char	*val;
	char	*new_env;
	int		ret;

	sep = split_mod(env_upd, "+=");
	var = ft_strdup(sep[0]);
	val = ft_strdup(sep[1]);
	arr_cleaner(sep);
	ret = ind_of_envvar(mimi, var);
	if (ret < 0)
		new_env = join_mod(var, "=", val);
	else
		new_env = ft_strjoin(mimi->env_arr[ret], val);
	envvar_update(mimi, new_env);
	strdel(&var);
	strdel(&val);
}

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

int		val_adder(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (i != 0 && var[i - 1] == '+' && var[i] == '=')
		{
			printf("ADDER RETURNS OK\n");
			return (1);
		}
		i++;
	}
	printf("VAR - [[%s]]\n", var);
	return (0);
}

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
			{
				printf("ADDER\n");
				printf("mimi->ch - %d\n", mimi->ch);
				upd_newenv(mimi, cmd[k]);
			}
			else
			{
				// if (mimi->ch == 1)
				// {
				// 	upd_newenv2(mimi, cmd[k]);
				// 	mimi->ch = 0;
				// }
				if (c_exp_sup2(mimi, cmd, k) == 0)
				{
					if (mimi->ch != 2)
						envvar_update(mimi, ft_strdup(cmd[k]));
				}
				// else if (mimi->ch != 2)
				// 	envvar_update(mimi, ft_strdup(cmd[k]));
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
