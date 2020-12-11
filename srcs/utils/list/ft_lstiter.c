#include "minishell.h"

void ft_lstiter(t_command *lst, void (*f)(void *))
{
	while (lst != 0)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
