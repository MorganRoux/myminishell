#include "../incs/minishell.h"

int		check_pres(char ch, char *str) // check if char is in the str
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (ch == str[k])
			return (1);
		k++;
	}
	return (0);
}

int		wrd_cnt(char *str, char *charset) // count words
{
	int	i;
	int	num;
	int	bl;

	i = 0;
	num = 0;
	while (str[i])
	{
		bl = 0;
		while (check_pres(str[i], charset) && str[i])
			i++;
		while (!check_pres(str[i], charset) && str[i])
		{
			num += (bl ? 0 : 1);
			bl = 1;
			i++;
		}
	}
	return (num);
}

char	*cutter(char *str, char *charset, int *i) // to cut words in the str
{
	int		j;
	int		len;
	char	*strnew;

	j = 0;
	len = 0;
	while (check_pres(str[*i], charset) && str[*i])
		*i += 1;
	while (!check_pres(str[*i + len], charset) && str[*i + len])
		len++;
	if (!(strnew = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (j < len)
	{
		strnew[j] = str[*i];
		j++;
		*i += 1;
	}
	strnew[j] = '\0';
	return (strnew);
}

char	**split_mod(char *str, char *charset)
{
	int		i;
	char	**dest;
	int		k;
	int		len_des;

	i = 0;
	k = 0;
	len_des = wrd_cnt(str, charset);
	if (!(dest = malloc(sizeof(char *) * (len_des + 1))))
		return (NULL);
	while (i < len_des)
	{
		dest[i] = cutter(str, charset, &k);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char		*join_mod(char const *s1, const char *s2, char const *s3)
{
	char	*temp;
	char	*res;

	if (!(temp = ft_strjoin(s1, s2)))
		return (NULL);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}