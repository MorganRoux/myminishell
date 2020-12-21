#include "minishell.h"

void    free_strs(char **strs)
{
    while(*strs != 0)
        free(*strs++);
}