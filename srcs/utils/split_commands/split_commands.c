#include "minishell.h"

char	**split_commands(char *line)
{
	return (ft_split(line, ';'));
}
