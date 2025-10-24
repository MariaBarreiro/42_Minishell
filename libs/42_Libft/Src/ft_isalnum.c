/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:21:39 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 09:25:50 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_isalnum: ceck if car is alphanumeric;
///int c: car to ceck;
///RETURN: SUCCESS: c:
///RETURN: FAILURE: 0;

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (8);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	// Array of test caracters
	int tests[] = {'a', 'Z', '5', '@', ' ', '\n', -1, 128};
	int i = 0;

	while (i < (int)(sizeof(tests) / sizeof(tests[0])))
	{
		int c = tests[i];
		printf("  ft_isalnum: %d\n", ft_isalnum(c));
		printf("  isalnum   : %d\n", isalnum(c));

		if (ft_isalnum(c) == isalnum(c))
			printf("MATCH\n");
		else
			printf("MISSMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
