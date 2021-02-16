#include "minishell.h"

int     ft_isalpha_u(char c)
{
	return ((ft_isalpha(c) || c == '_') ? 1 : 0);
}

int     ft_isalnum_u(char c)
{
	return ((ft_isalnum(c) || c == '_') ? 1 : 0);
}