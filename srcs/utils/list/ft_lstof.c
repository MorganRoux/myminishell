#include "minishell.h"

t_list *ft_lstof(t_list *lst, int index)
{
	t_list	*list;
    int i;

    i = 0;
	if (lst == 0)
		return (0);
	list = lst;
	while (list->next != 0 && i++ < index)
    {
        list = list->next;
    }
	return (list);
}