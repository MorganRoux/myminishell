/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:15:20 by alkanaev          #+#    #+#             */
/*   Updated: 2021/01/29 13:47:48 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	char	**splitted;
	char	*ret;

	splitted = ft_split(str, '=');
	if (splitted == NULL)
		return (NULL);
	ret = ft_strdup(splitted[0]);
	free_strs(splitted);
	return (ret);
}

int		get_var_index(char *envp[], char *text)
{
	char	*var;
	int		i;

	i = 0;
	var = ft_strjoin(text, "=");
	while (ft_strnstr(envp[i], var, ft_strlen(var)) == NULL)
	{
		if (envp[++i] == 0)
		{
			free(var);
			return (-1);
		}
	}
	free(var);
	return (i);
}

char	*get_var(char *envp[], char *text)
{
	char	*res;
	char	*var;

	var = ft_strjoin(text, "=");
	while ((res = ft_strnstr(*envp, var, ft_strlen(var))) == NULL)
	{
		if (*(++envp) == 0)
		{
			free(var);
			res = malloc(1);
			res[0] = '\0';
			return (res);
		}
	}
	res = ft_substr(res, ft_strlen(var), ft_strlen(res));
	free(var);
	return (res);
}
