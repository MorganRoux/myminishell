#include "minishell.h"

char    *get_var(char *envp[], char *text)
{
    char    *res;
    char    *var;

    var = ft_strjoin(text, "=");
    while(!(res = ft_strnstr(*envp, var, ft_strlen(var))))
    {
        if(*(++envp) == 0)
            return NULL;
    }
    res = ft_substr(res, ft_strlen(var), ft_strlen(res));
    free(var);
    return res;
}