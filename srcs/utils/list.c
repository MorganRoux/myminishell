#include "minishell.h"

t_command   *new_command(t_command *prev)
{
    t_command   *ret;
    if(!(ret = (t_command *)malloc(sizeof(t_command *))))
        return NULL;
    if (prev != NULL)
        prev->next = ret;
    return ret;
}