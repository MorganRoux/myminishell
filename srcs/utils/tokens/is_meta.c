#include "minishell.h"

int     is_meta_char(char c)
{
    char    METACHARACTER[] = " \t\n|&;()<>";
    int     i;

    i = 0;
    while (METACHARACTER[i] != 0)
    {
        if (METACHARACTER[i] == c)
            return 1;
        i++;
    }
    return 0;
}

int     is_meta_str(char *c)
{
    char    METACHARACTER[] = " \t\n|&;()<>";
    int     i;

    i = 0;
    while (METACHARACTER[i] != 0)
    {
        if (METACHARACTER[i] == c[0])
            return 1;
        i++;
    }
    return 0;
}