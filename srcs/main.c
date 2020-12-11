#include "minishell.h"

int main()  
{
    char    *line;
    t_command   *cmds;
    
    line = NULL;
    while (1) 
    {
        ft_printf("Minishell:>");
        if (get_next_line(0, &line) == -1)
            return (0);
        if ((cmds = parse(line)) == NULL)
            return (0);
        exec(cmds);
        //ft_printf("%s", line);
    }
}   