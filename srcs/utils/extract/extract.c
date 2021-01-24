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

char   **extract_command(char **strs, t_command *cmd)
{
    *strs = ft_strdup(cmd->exec);
    strs++;
    return strs;
}

char    **extract_args(char **strs, t_command *cmd)
{
    t_list_str  *args;

    args = cmd->args;
    while (args != 0)
    {
        *strs++ = ft_strdup(args->content);
        args = args->next;
    }
    return strs;
}

char    **extract_command_and_args(t_command *cmd)
{
    char        **strs;
    int         count;

    count = ft_lstsize(cmd->args) + 1;
    strs = malloc((count + 1) * sizeof(char *));
    strs = extract_command(strs, cmd);
    strs = extract_args(strs, cmd);
    *strs = 0;
    strs = strs - count;
    return (strs);
}