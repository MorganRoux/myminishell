#include "../incs/minishell.h"

t_command		glob_command;

int main(int argc, char *argv[], char *const envp[])  
{
    char        *line;
    t_list_cmd  *cmds;
    int         i;
    char        **cmd;

    line = NULL;
    i = 1;
    ft_bzero(&glob_command, sizeof(t_command));

    while (i != 0) 
    {
        ft_printf("Minishell:>");
        if ((i = get_next_line(0, &line)) == -1)
            return (0);
        if ((cmds = parse(line)) == NULL)
            return (0);
        cmd = the_bridge(cmds);
        exec1(cmds, envp);
        //exec2(&glob_command, cmd, cmds);
    }
}   