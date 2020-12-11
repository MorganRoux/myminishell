#include "minishell.h"

void ft_lstdelone(t_command *lst, void (*del)(void*))
{
	(*del)(lst->content);
	free(lst);
}
	
