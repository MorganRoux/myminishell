/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:53:03 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:10:00 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	strdel(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
}

void	arr_cleaner(char **str)
{
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

/*
** search for
*/

int		ind_of_envvar(t_command *mimi, char *var)
{
	int		i;
	char	*varenv;
	char	**sep;
	int		len;

	sep = split_mod(var, "=");
	varenv = ft_strdup(sep[0]);
	arr_cleaner(sep);
	len = ft_strlen(varenv);
	i = 0;
	while (mimi->env_arr[i])
	{
		if (!strncmp(mimi->env_arr[i], varenv, len))
		{
			free(varenv);
			return (i);
		}
		i++;
	}
	free(varenv);
	return (-1);
}

void	del_envvar(t_command *mimi, char *var)
{
	int		i;
	int		j;
	int		ind;
	char	**tmp;
	int		len;

	i = 0;
	j = 0;
	ind = ind_of_envvar(mimi, var);
	if (ind == -1)
		return ;
	len = cnt_com_parts(mimi->env_arr);
	if (!(tmp = (char **)ft_calloc(sizeof(char *), len + 1)))
		return ;
	while (mimi->env_arr[i])
	{
		if (i != ind)
		{
			tmp[j] = ft_strdup(mimi->env_arr[i]);
			j++;
		}
		i++;
	}
	arr_cleaner(mimi->env_arr);
	mimi->env_arr = tmp;
}

/*
** update variables from env_arr // if var exists - we remove it first
*/

void	envvar_update(t_command *mimi, char *var)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	del_envvar(mimi, var);
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
	tmp[j] = ft_strdup(var);
	arr_cleaner(mimi->env_arr);
	mimi->env_arr = tmp;
	strdel(&var);
}
