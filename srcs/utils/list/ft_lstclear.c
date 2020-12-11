#include "minishell.h"

void ft_lstclear(t_command **lst, void (*del)(void*))
{
	t_command	*list;
	t_command	*prev;

	if (lst == NULL)
		return;
	list = *lst;
	while (list != 0)
	{
		prev = list;
		list = list->next;
		ft_lstdelone(prev, del);
	}
	*lst = 0;
}
