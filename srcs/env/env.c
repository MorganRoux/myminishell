#include "minishell.h"

char    *get_var(char *envp[], char *text)
{
    char *var;

    while(!(var = ft_strnstr(*envp, text, ft_strlen(text))))
    {
        if(*(++envp) == 0)
            return NULL;
    }
    var = ft_substr(var, ft_strlen(text), ft_strlen(var));
    return var;
}