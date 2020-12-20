#include "minishell.h"

char    **list2char(t_list_cmd *cmds)
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
    strs[count] = 0;
    return (strs);
}

char    **cmd2char(t_command *cmd)
{
    char        **strs;
    int         count;
    t_list_str  *args;

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
    strs[count] = 0;
    return (strs);
}