#include "minishell.h"

int             pass_quoting(char *s, char c)
{
    char *str;

    str = s;
    s++;
    while (*s != 0)
    {
        if(*s == c && *(s - 1) != '\\')
            return ++s - str;
        s++;
    }
    return -1;
}

int             word_len(char *s)
{
    int len;
    int l;

    len = 0;
    while (*s != 0 && !is_meta_char(*s))
    {
        if (*s == '"' || *s == '\'')
            l = pass_quoting(s, *s);

        else
            l = 1;
        if (l == -1)
            return -1;
        len += l;
        s += l;
    }
    return len;
}

t_list			*split_tokens(char *s)
{
	t_list  *ret;
    t_list  *new;
    char    *str;
    int     len;

    ret = NULL;
    while (*s != 0)
    {
        if (is_meta_char(*s))
            len = 1;
        else
            len = word_len(s);
        if (len == -1)
            return NULL;
        str = ft_substr(s,0,len);
        new = ft_lstnew(str);
        ft_lstadd_back(&ret, new);
        s = s + len;
    }
    return ret;
}
