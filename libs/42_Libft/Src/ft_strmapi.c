/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:40:21 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 10:32:32 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strmapi: Applies the function f to each char of the string s, 
///passing its index as the first argument and the char as the second.
///s: String to iterate over;
///f: Function to apply to each character;
///RETURN: SUCCESS: String created from the successive applications of 'f';
///RETURN: FAILURE: Null;

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*str;
	size_t		len;
	size_t		i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	ft_to_upper(unsigned int i, char c)
{
	(void)i;

	if(c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

#include <stdio.h>

int	main(void)
{
	// ---------- Test 1: normal lowercase string ----------
	const char *str1 = "hello";
	char *res1 = ft_strmapi(str1, ft_to_upper);
	printf("Input       : \"%s\"\n", str1);
	printf("ft_strmapi  : \"%s\"\n", res1);
	free(res1);
	printf("----------------------------------\n");

	// ---------- Test 2: empty string ----------
	const char *str2 = "";
	char *res2 = ft_strmapi(str2, ft_to_upper);
	printf("Input       : \"%s\"\n", str2);
	printf("ft_strmapi  : \"%s\"\n", res2);
	free(res2);
	printf("----------------------------------\n");

	// ---------- Test 3: string with non-letter characters ----------
	const char *str3 = "123!@# abc";
	char *res3 = ft_strmapi(str3, ft_to_upper);
	printf("Input       : \"%s\"\n", str3);
	printf("ft_strmapi  : \"%s\"\n", res3);
	free(res3);
	printf("----------------------------------\n");

	// ---------- Test 4: NULL string ----------
	const char *str4 = NULL;
	char *res4 = ft_strmapi(str4, ft_to_upper);
	printf("Input       : NULL\n");
	if (res4 == NULL)
		printf("ft_strmapi  : NULL \n");
	else
	{
		printf("ft_strmapi  : \"%s\"\n", res4);
		free(res4);
	}
	printf("----------------------------------\n");

	return 0;
}*/
