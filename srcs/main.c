#include "../incs/minishell.h"

void		env_filling(char **envp, t_command *glob_command) //ADD SAFE FUNC
{
	int			i;
	int			len;

    i = 0;
	len = cnt_com_parts(envp);
	glob_command->env_arr = (char **)ft_calloc(sizeof(char *), (len + 1));
	if (!(glob_command->env_arr))
	    close_mimi(glob_command, 1);
	while (envp[i])
	{
		glob_command->env_arr[i] = ft_strdup(envp[i]);
	if (!(glob_command->env_arr))
	    close_mimi(glob_command, 1);
		i++;
	}
}

int main(int argc, char *argv[], char *envp[]/*, char **env*/)  
{
    char        *line;
    t_list_cmd  *cmds;
    int         i;
    t_command	glob_command;

    (void)argc;
    (void)argv;
    line = NULL;
    i = 1;
    ft_bzero(&glob_command, sizeof(t_command));
    env_filling(envp, &glob_command);
    while (i != 0) 
    {
        ft_printf("Minishell:>");
        if ((i = get_next_line(0, &line)) == -1)
            return (0);
        if ((cmds = parse(line, glob_command.env_arr)) == NULL)
            return (0);
        exec(&glob_command, cmds);
    }
}   