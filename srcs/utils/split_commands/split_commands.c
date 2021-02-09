/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:56:07 by alkanaev          #+#    #+#             */
/*   Updated: 2021/02/09 11:56:27 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_sep(char c)
{
	return ((c == ';' || c == '|') ? 1 : 0);
}

static	size_t	count_words(char const *s)
{
	size_t	n;

	n = 0;
	while (*s != 0)
	{
		while (is_sep(*s))
			s++;
		if (*s != 0)
		{
			n++;
			while (!is_sep(*s) && *s != 0)
				s++;
		}
	}
	return (n);
}

static	char	**alloc_mem(int n_words, char const *s)
{
	char	**strs;
	char	**ret;
	int		len;

	len = 0;
	if (!(strs = (char **)malloc((n_words + 1) * sizeof(char *))))
		return (NULL);
	ret = strs;
	strs[n_words] = 0;
	while (n_words-- > 0)
	{
		len = 0;
		while (is_sep(*s))
			s++;
		while (!is_sep(s[len]) && s[len] != 0)
			len++;
		s += len;
		if (!(*strs = (char *)malloc((len + 2) * sizeof(char))))
			return (NULL);
		strs++;
	}
	return (ret);
}

char			**ftt_split(char const *s)
{
	size_t	n_words;
	size_t	i;
	char	**ret;
	char	**strs;

	n_words = count_words(s);
	strs = alloc_mem(n_words, s);
	ret = strs;
	while (n_words-- > 0)
	{
		i = 0;
		while (is_sep(*s))
			s++;
		while (!is_sep(*s) && *s != 0)
			(*strs)[i++] = *s++;
		(*strs)[i++] = *s++;
		(*strs++)[i] = 0;
	}
	return (ret);
}

int				command_len(char *s)
{
	int			len;
	int			l;
	static int	escape;

	len = 0;
	escape = 0;
	while (*s != 0 && (!is_sep(*s) || escape == 1))
	{
		l = 1;
		if (*s == '"' && escape == 0)
			l = pass_dquotes(s);
		else if (*s == '\'' && escape == 0)
			l = pass_squotes(s);
		else if (*s == '\\' && escape == 0)
			escape = 1;
		else
			escape = 0;
		if (l == -1)
			return (-1);
		len += l;
		s += l;
	}
	return (len);
}
