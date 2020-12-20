#include "../incs/minishell.h"

t_command		glob_command;

int main(int argc, char *argv[], char *envp[])  
{
    (void)argc;
    (void)argv;
    (void)envp;
    char        *line;
    t_list_cmd  *cmds;
    int         i;

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
        //exec1(cmds);
        exec2(&glob_command, cmds, envp);
    }
}   