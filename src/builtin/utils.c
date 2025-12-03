#include "built.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	c1 = *(unsigned char *)s1;
	c2 = *(unsigned char *)s2;
	return (c1 - c2);
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
		return (NULL);
	while (n < i)
	{
		dup[n] = s[n];
		n++;
	}
	dup[n] = '\0';
	return (dup);
}

char	*ft_substr_split(char const *s, unsigned int start, size_t len)
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}


static size_t	ft_counter(const char *s, char c);
static char		**ft_alloc_split(const char *s, char c);
static size_t	ft_count(char const *s, int *start, size_t i, char c);
static int		free_split(char **split, size_t filled);

char	**ft_split(char const *s, char c)
{
	int			start;
	size_t		i;
	size_t		word;
	char		**split;

	i = 0;
	word = 0;
	if (!s)
		return (0);
	split = ft_alloc_split(s, c);
	if (!split)
		return (0);
	while (s[i])
	{
		i = ft_count(s, &start, i, c);
		if (s[i] == '\0' && start == -1)
			break ;
		split[word++] = ft_substr_split(s, start, (i - start));
		if (!split[word - 1])
			return (free_split(split, word), NULL);
		start = -1;
	}
	split[word] = NULL;
	return (split);
}

///ft_count: Finds the next word (substr) and returns its index; 
///Char const *s: Input str;
///int *start: Stores the starting index of the next word (output);
///size_t i: Current index in str;
///char c: Delimiter char;
///RETURN: SUCCESS: Index after the current word 
///					(to continue iterating in split);

static size_t	ft_count(char const *s, int *start, size_t i, char c)
{
	*start = -1;
	while (s[i] == c)
		i++;
	if (s[i])
	{
		*start = i;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (i);
}

static char	**ft_alloc_split(const char *s, char c)
{
	char	**split;
	size_t	count;

	count = ft_counter(s, c);
	split = (char **)malloc((count + 1) * sizeof(char *));
	return (split);
}

static size_t	ft_counter(const char *s, char c)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word_count);
}

static int	free_split(char **split, size_t filled)
{
	size_t	i;

	i = 0;
	while (i < filled)
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	return (free(split), 0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

int	ft_lstsize(t_env *lst)
{
	int		i;
	t_env	*list;

	i = 0;
	list = lst;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (8);
	return (0);
}

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

int	ft_atoll(const char *nptr)
{
	size_t				i;
	int long long		result;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}
