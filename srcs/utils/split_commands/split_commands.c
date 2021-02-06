#include "minishell.h"


int             is_sep(char c)
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


int			command_len(char *s)
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

t_list_str	*split_commandss(char *s)
{
	t_list_str	*ret;
	t_list_str	*new;
	char		*str;
	int			len;

	ret = NULL;
	while (*s != 0)
	{
		len = command_len(s);
		if (len == -1)
		{
			ft_printf("error near %c\n", *s);
			ft_lstclear(&ret, free);
			return (NULL);
		}
		str = ft_substr(s, 0, len + 1);
		new = ft_lstnew(str);
		ft_lstadd_back(&ret, new);
		s = s + len + (s + len == 0 ? 0 : 1);
	}
	return (ret);
}

char	**split_commands(char *line)
{
	t_list_str	*lst;
	char		**strs;

	lst = split_commandss(line);
	strs = list2char(lst);
	ft_lstclear(&lst, free);
	//return (ftt_split(line));
	return (strs);
}