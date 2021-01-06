#include "../incs/minishell.h"

t_command		glob_command;

void		env_filling(char **envp) //ADD SAFE FUNC
{
	int			i;
	int			len;

	len = cnt_com_parts(envp);
	glob_command.env_arr = (char **)ft_calloc(sizeof(char *), (len + 1));
	//if (!(glob_command.env_arr))
	    //FUNCTION FOR LEAVING THE PROGR
	i = 0;
	while (envp[i])
	{
		glob_command.env_arr[i] = ft_strdup(envp[i]);
	//if (!(glob_command.env_arr))
	    //FUNCTION FOR LEAVING THE PROGR
		i++;
	}
}

//int      close_mimi()
//{
//
//}

int main(int argc, char *argv[], char *envp[]/*, char **env*/)  
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
    env_filling(envp);
    while (i != 0) 
    {
        ft_printf("Minishell:>");
        if ((i = get_next_line(0, &line)) == -1)
            return (0);
        if ((cmds = parse(line)) == NULL)
            return (0);
        exec(&glob_command, cmds, envp);
    }
}   