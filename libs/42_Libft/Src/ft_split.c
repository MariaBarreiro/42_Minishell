/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:58:44 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/12 15:43:03 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_counter(const char *s, char c);
static char		**ft_alloc_split(const char *s, char c);
static size_t	ft_count(char const *s, int *start, size_t i, char c);
static int		free_split(char **split, size_t filled);

///ft_split: Splits a str into an array of substrs based on a given delimiter;
///s: String to be split;
///c: Delimiter character/substrings NOT equal to c but separated by it;
///RETURN: SUCCESS: Array of new strings resulting from the split;
///RETURN: FAILURE: Null;

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
		split[word++] = ft_substr(s, start, (i - start));
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

///ft_alloc_split: Allocs memory for the result array;
///Const char *s: Input str to split;
///Char c: Delimiter;
///RETURN: SUCCESS: Allocated array of pointers;
///RETURN: FAILURE: Null;

static char	**ft_alloc_split(const char *s, char c)
{
	char	**split;
	size_t	count;

	count = ft_counter(s, c);
	split = (char **)malloc((count + 1) * sizeof(char *));
	return (split);
}

///ft_counter: Counts how many strs will be created;
///const char *s: Str to count words in;
///char c: Delimiter char;
///RETURN: SUCCESS: Word count;

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

///free_split: Frees all substrs in the array if allocation fails;
///char **split: Array of substrs;
///size_t filled: How many substrs were successfully allocated;

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
/*

#include <stdio.h>


int	main(void)
{
	const char *input = "            ";
	char delim = ' ';
	char **result = ft_split(input, delim);

	// Print each word in the result
	int i = 0;
	while (result && result[i])
	{
		printf("  [%d]: \"%s\"\n", i, result[i]);
		i++;
	}
	printf("  [%d]: NULL\n", i); // Confirm the array ends with NULL

	// Free the allocated memory
	i = 0;
	while (result && result[i])
		free(result[i++]);
	free(result);

	return 0;
}
*/
