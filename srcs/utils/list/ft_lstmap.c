#include "minishell.h"

t_command	*ft_lstmap(t_command *lst, void *(*f)(void *),void (*del)(void *))
{
	t_command	*new;
	t_command	*ret;
	
	if (lst == 0)
		return (0);
	if (!(ret = (t_command *)malloc(sizeof(t_command))))
	{
		ft_lstclear(&ret, del);
		return (0);
	}
	ret->content = (*f)(lst->content);
	new = ret;
	while(lst->next != 0)
	{
		lst = lst->next;
		if (!(new->next = (t_command *)malloc(sizeof(t_command))))
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		new = new->next;
		new->content = (*f)(lst->content);
	}
	new->next = 0;
	return (ret);
}
