#include "minishell.h"

void    print_strs(char **strs)
{
    while (*strs != NULL)
    {
        ft_printf("%s\n", *strs);
        strs++;
    }
}