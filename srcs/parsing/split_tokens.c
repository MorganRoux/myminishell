#include "minishell.h"

int             pass_dquotes(char *s)
{
    char *str;

    str = s;
    s++;
    while (*s != 0)
    {
        if(*s =='"' && *(s - 1) != '\\')
            return (++s - str);
        s++;
    }
    return (-1);
}

int             pass_squotes(char *s)
{
    char *str;

    str = s;
    s++;
    while (*s != 0)
    {
        if(*s =='\'')
            return (++s - str);
        s++;
    }
    return (-1);
}

int             word_len(char *s)
{
    int len;
    int l;
    static int escape = 0;

    len = 0;
    while (*s != 0 && (!is_meta_char(*s) || escape == 1))
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

int     meta_len(char *str)
{
    if (*str == '>' && *(str + 1) == '>')
        return (2);
    else
        return (1);
}

t_list_str			*split_tokens(char *s)
{
	t_list_str  *ret;
    t_list_str  *new;
    char        *str;
    int         len;

    ret = NULL;
    while (*s != 0)
    {
        if (is_meta_char(*s))
            len = meta_len(s);
        else
            len = word_len(s);
        if (len == -1)
        {
            print_lst_str(ret);
            ft_lstclear(&ret, free);
            print_lst_str(ret);
            return (NULL);
        }
            
        str = ft_substr(s,0,len);
        new = ft_lstnew(str);
        ft_lstadd_back(&ret, new);
        s = s + len;
    }
    return (ret);
}
