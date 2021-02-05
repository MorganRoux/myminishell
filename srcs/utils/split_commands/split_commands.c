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
		if (!(*strs = (char *)malloc((len + 1) * sizeof(char))))
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
		(*strs++)[i] = 0;
	}
	return (ret);
}

char	**split_commands(char *line)
{
	return (ftt_split(line));
}