/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:29:50 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/14 17:56:27 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** to manage envvar_pr_sort (part of sorting)
*/

void    envvar_sort(char **env_arr, int len)
{
	int		k;
	char	*tmp;
    int		sort;

	sort = 0;
	while (env_arr && sort == 0)
	{
		sort = 1;
		k = 0;
		while (k < len - 1)
		{
			if (ft_strcmp(env_arr[k], env_arr[k + 1]) > 0)
			{
				tmp = env_arr[k];
				env_arr[k] = env_arr[k + 1];
				env_arr[k + 1] = tmp;
				sort = 0;
			}
			k++;
		}
		len--;
	}
}

char    *ft_strndup(char *str, long len)
{
	char *tmp;
	long i;

	i = 0;
	tmp = NULL;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}

/*
** to manage envvar_pr_sort (part of printing)
*/

void    envvar_print(char *env_arr)
{
	char	*var;
	char	*val;
	int		i;

	i = 0;
    val = NULL;
	while (env_arr[i] && env_arr[i] != '=')
		i++;
	var = ft_strndup(env_arr, i);
	if (env_arr[i] == '=')
		val = ft_strdup(&env_arr[++i]);
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	if (val)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(val, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	strdel(&val);
	strdel(&var);
}

void		envvar_pr_sort(t_command *mimi)
{
	int		argc;
	char	**tmp;
    int		i;
	int		j;

	i = 0;
	j = 0;
    argc = cnt_com_parts(mimi->env_arr);
	tmp = (char **)ft_calloc(sizeof(char *), argc + 1);
	while (i < argc)
	{
		tmp[j] = ft_strdup(mimi->env_arr[i]);
		i++;
		j++;
	}
	envvar_sort(tmp, cnt_com_parts(tmp));
	j = 0;
	while (j < argc)
	{
		envvar_print(tmp[j]);
		j++;
	}
	arr_cleaner(tmp);
	mimi->ret = 0;
}

/*
** taken from export.c because of the "5 funcs" rule
*/

int		space_checker(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t'
        || str[i] == '\n' || str[i] == '\r'
        || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}