/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:31:48 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 09:34:47 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_isascii: Check if char is ascii;
///int c: char to check;
///RETURN: SUCCESS: c:
///RETURN: FAILURE: 0;

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int tests[] = {'A', '0', 0, 127, -1, 128, 255};
	int i = 0;

	while (i < (int)(sizeof(tests) / sizeof(tests[0])))
	{
		int c = tests[i];

		int ft = ft_isascii(c);
		int std = isascii(c);  // isascii is safe with all int values

		printf("  ft_isascii: %d\n", ft);
		printf("  isascii   : %d\n", std);

		if (ft == std)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
