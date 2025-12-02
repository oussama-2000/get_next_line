#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= strlen(s))
		return (strdup(""));
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = start;
	j = 0;
	while (len > 0)
	{
		sub[j] = s[i];
		i++;
		j++;
		len--;
	}
	sub[j] = '\0';
	return (sub);
}