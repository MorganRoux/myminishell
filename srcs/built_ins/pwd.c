/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:01:54 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/14 18:05:51 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** we are looking for an index of the char needed
** ret = -1 if a char isnt found
*/

int		get_char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
** here we check that size of written var is equal to env's var
**
** len_checker = (get_char_pos(env_arr[i], '=') == (int)ft_strlen(var)); 
** 		get len of arg after $ and compare len==ind - so we get 1 or 0
**
** if (len_checker &&
**			(!ft_strncmp(env_arr[i], var, get_char_pos(env_arr[i], '='))))
** 		compare len of our var with one of existing variablesd
** return (ft_strchr(env_arr[i], '=') + 1);
** 		1 to skip the =
*/

char	*var_checker(t_command *mimi, char **env_arr, char *var)
{
	int	i;
	int len_checker;

	(void)mimi;
	i = 0;
	if (!env_arr)
		return (NULL);
	while (env_arr[i])
	{
		len_checker = (get_char_pos(env_arr[i], '=') == (int)ft_strlen(var));
		if (len_checker &&
			(!ft_strncmp(env_arr[i], var, get_char_pos(env_arr[i], '='))))
			return (ft_strchr(env_arr[i], '=') + 1);
		i++;
	}
	return (NULL);
}

/*
** ret = 0 if no err
*/

void	com_pwd(t_command *mimi) 
{
	char	*cur_dir;

	cur_dir = var_checker(mimi, mimi->env_arr, "PWD");
	if (cur_dir)
	{
		ft_putendl_fd(cur_dir, 1);
		mimi->ret = 0;
	}
	else
		mimi->ret = 1;
}
