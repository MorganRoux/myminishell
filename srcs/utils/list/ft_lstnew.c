#include "minishell.h"

t_command *ft_lstnew()
{
	t_command	*list;

	if (!(list = (t_command *) malloc(sizeof(t_command))))
		return (0);
	list->next = 0;
	return (list);
}
