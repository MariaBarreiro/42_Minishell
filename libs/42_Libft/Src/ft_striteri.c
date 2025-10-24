/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:39:11 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 08:57:14 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_striteri: Applies the function 'f' to each char of the str passed
///						as an argument, passing its index as the 1st argument.
///s: String to iterate over;
///f: Function to apply to each char;
///NO RETURN VALUE;

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t		i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	ft_to_upper(unsigned int i, char *c)
{
	(void)i;

	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

#include <stdio.h>

int	main(void)
{
	char str1[] = "hello world";
	char str2[] = "";
	char *null_str = NULL;

	// Test 1: Normal lowercase string
	printf("Before ft_striteri: %s\n", str1);
	ft_striteri(str1, ft_to_upper);
	printf("After  ft_striteri: %s\n", str1);
	printf("----------------------------------\n");

	// Test 2: Empty string
	printf("Before ft_striteri (empty): \"%s\"\n", str2);
	ft_striteri(str2, ft_to_upper);
	printf("After  ft_striteri (empty): \"%s\"\n", str2);
	printf("----------------------------------\n");

	// Test 3: NULL string (should do nothing)
	printf("Test with NULL string:\n");
	ft_striteri(null_str, ft_to_upper);
	printf("No crash\n");
	printf("----------------------------------\n");

	// Test 4: NULL function (should do nothing)
	printf("Test with NULL function:\n");
	ft_striteri(str1, NULL);
	printf("No crash\n");

	return 0;
}*/
