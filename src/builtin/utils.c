#include "built.h"


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	n;
	char	*dup;

	n = 0;
	i = ft_strlen(s);
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (n < i)
	{
		dup[n] = s[n];
		n++;
	}
	dup[n] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	k;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (0);
	k = ft_strlen(s);
	i = 0;
	j = start;
	if (j >= k)
		return (ft_strdup(""));
	if (len > (k - j))
		len = k - j;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[j] && i < len)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = '\0';
	return (sub);
}