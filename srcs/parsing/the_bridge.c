#include "minishell.h"

char    **the_bridge(t_list_cmd *cmds)
{
    char        **strs;
    t_command   *cmd;
    int         count;
    t_list_str  *args;

    cmd = cmds->content;
    count = ft_lstsize(cmd->args) + 1;
    strs = malloc((count + 1) * sizeof(char *));
    strs[0] = cmd->exec;
    args = cmd->args;
    count = 1;
    while (args != 0)
    {
        strs[count++] = args->content;
        args = args->next;
    }
    return (strs);
}