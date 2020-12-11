#include "minishell.h"

t_command *ft_lstlast(t_command *lst)
{
	t_command	*list;

	if (lst == 0)
		return (0);
	list = lst;
	while (list->next != 0)
		list = list->next;
	return (list);
}
