#include "minishell.h"

int main()  
{
    char        *line;
    t_list_cmd  *cmds;
    int         i;

    line = NULL;
    i = 1;
    while (i > 0) 
    {
        ft_printf("Minishell:>");
        if ((i = get_next_line(0, &line)) == -1)
            return (0);
        if ((cmds = parse(line)) == NULL)
            return (0);
        exec(cmds);
    }
}   