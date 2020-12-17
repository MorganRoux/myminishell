#include "minishell.h"

t_list_cmd  *ft_lstinit()
{
	t_list      *list;
    t_command   *cmd;
	if (!(cmd = (t_command *) malloc(sizeof(t_command))))
		return (0);
	list = ft_lstnew(cmd);
	return (list);
}
