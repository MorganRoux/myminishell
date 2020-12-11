#include "minishell.h"

void ft_lstadd_back(t_command **alst, t_command *new)
{
	t_command	*list;
	
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	list = *alst;
	while (list->next != 0)
		list = list->next;
	list->next = new;
	return ;

}
