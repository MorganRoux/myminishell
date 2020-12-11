#include "minishell.h"

void ft_lstadd_front(t_command **alst, t_command *new)
{
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	new->next = *alst;
	*alst = new;
	return ;
}
