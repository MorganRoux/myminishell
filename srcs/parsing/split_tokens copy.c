#include "minishell.h"

size_t             pass_quoting(char **s, char c)
{
    char *str;

    str = *s;
    (*s)++;
    while (**s != 0)
    {
        if(*(*s)++ == c)
            return *s - str + 1;
    }
    return 0;
}

size_t	count_words(char *s, char c)
{
	size_t	n;

    while (*s == c) s++;
    if (*s == 0)
        return 0;
	n = 1;
	while (*s != 0)
	{
        if (*s == c)
        {
            while (*s == c) s++;
            n = (*s == 0) ? n : n + 1;
        }		
		else if (*s == '"' || *s == '\'')
        {
            if (pass_quoting(&s, *s) == 0)
                return 0;
        }
        else
			s++;
	}
	return (n);
}

// char	**alloc_mem(int n_words, char *s, char c)
// {
// 	char	**strs;
// 	char	**ret;
// 	int		len;

// 	len = 0;
// 	if (!(strs = (char **)malloc((n_words + 1) * sizeof(char *))))
// 		return (NULL);
// 	ret = strs;
// 	strs[n_words] = 0;
// 	while (n_words-- > 0)
// 	{
// 		len = 0;
// 		while (*s == c)
// 			s++;
// 		while (s[len] != c && s[len] != 0)
// 			len++;
// 		s += len;
// 		if (!(*strs = (char *)malloc((len + 1) * sizeof(char))))
// 			return (NULL);
// 		strs++;
// 	}
// 	return (ret);
// }

char			**split_tokens(char *s)
{
	size_t	n_words;
	// size_t	i;
	// char	**ret;
	// char	**strs;
    char    c = ' ';

    if (ft_strlen(s) <= 0)
        return NULL;
	if ((n_words = count_words(s, c)) == 0)
    {
        ft_printf("nword: %d", n_words);
        return NULL;
    }
    ft_printf("nword: %d", n_words);
	// strs = alloc_mem(n_words, s, c);
	// ret = strs;
	// while (n_words-- > 0)
	// {
	// 	i = 0;
	// 	while (*s == c)
	// 		s++;
	// 	while (*s != c && *s != 0)
	// 		(*strs)[i++] = *s++;
	// 	(*strs++)[i] = 0;
	// }
	// return (ret);
    return NULL;
}
