/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:16:02 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:37:20 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		val_adder(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (i != 0 && var[i - 1] == '+' && var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
