#include "../incs/minishell.h"

t_command		glob_command;

int main()  
{
    char        *line;
    t_list_cmd  *cmds;
    
    line = NULL;
    ft_bzero(&glob_command, sizeof(t_command));
    while (1) 
    {
        ft_printf("Minishell:>");
        if (get_next_line(0, &line) == -1)
            return (0);
        if ((cmds = parse(line)) == NULL)
            return (0);
        exec1(cmds);
        //exec2(&glob_command, &line, cmds);
    }
}   