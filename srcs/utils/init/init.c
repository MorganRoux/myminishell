#include "minishell.h"

t_command	g_globstruct;

void    init_globals(char *envp[], t_command *g_globstruct)
{
    int len;
    int i;

    i = -1;
    ft_bzero(g_globstruct, sizeof(t_command));
    len = get_strs_len(envp);
    g_globstruct->env_arr = (char **) calloc(sizeof(char *), (len + 1));
    while (++i < len)
        g_globstruct->env_arr[i] = ft_strdup(envp[i]);
}

/*
** SIGINT : ^C
** SIGQUIT : ^\
*/

void		sig_int(int signal)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (!(g_globstruct.pid))
		prompt();
	else
	{
		prompt();
		kill(g_globstruct.pid, signal);
	}
	g_globstruct.ret = 130;
}

void		sig_quit(int signal)
{
	if (g_globstruct.pid)
	{
		kill(g_globstruct.pid, signal);
		g_globstruct.ret = 131;
		ft_putstr_fd("\nquit (core dumped)\n", STDERR_FILENO);
	}
}

void    signal_callback()
{
    signal(SIGQUIT, &sig_quit);
    signal(SIGINT, &sig_int);
}