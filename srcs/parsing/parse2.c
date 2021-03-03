/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroux <mroux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:41:14 by mroux             #+#    #+#             */
/*   Updated: 2021/03/03 21:41:15 by mroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			solve_dquotes(char **str, char **content)
{
	(*content)++;
	while (**content != '"')
	{
		if (**content == 0)
			return (-1);
		if (**content == '\\'
			&& (*(*content + 1) == '$' || *(*content + 1) == '`' ||
			*(*content + 1) == '"' || *(*content + 1) == '!' ||
			*(*content + 1) == '\\'))
		{
			(*content)++;
			*(*str)++ = *(*content)++;
		}
		else
			*(*str)++ = *(*content)++;
	}
	(*content)++;
	return (0);
}

int			solve_squotes(char **str, char **content)
{
	(*content)++;
	while (**content != '\'')
	{
		if (**content == 0)
			return (-1);
		*(*str)++ = *(*content)++;
	}
	(*content)++;
	return (0);
}

int			solve_escape(char **str, char **content)
{
	(void)str;
	(*content)++;
	return (1);
}

int			solve_word(char **str, char **content)
{
	*(*str)++ = *(*content)++;
	return (0);
}

char		*solve_quotings(char *content)
{
	static int	escape;
	char		*str;
	char		*ret;
	char		*start;

	start = content;
	escape = 0;
	if (!(ret = (char *)malloc(ft_strlen(content) + 1)))
		return (NULL);
	str = ret;
	while (*content != 0)
	{
		if (*content == '"' && escape == 0)
			solve_dquotes(&str, &content);
		else if (*content == '\'' && escape == 0)
			solve_squotes(&str, &content);
		else if (*content == '\\' && escape == 0)
			escape = solve_escape(&str, &content);
		else
			escape = solve_word(&str, &content);
	}
	*str = 0;
	free(start);
	return (ret);
}
