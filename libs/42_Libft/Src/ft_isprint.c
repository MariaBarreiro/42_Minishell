/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:35:19 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 09:38:07 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_isprint: Checks if char c is printable;
///int c: Char to check;
///RETURN: SUCCESS: c;
///RETURN: FAILURE: 0;

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int tests[] = {'A', 'z', ' ', '9', '~', '\n', '\t', 0, -1, 127, 128, 255};
	int i = 0;

	while (i < (int)(sizeof(tests) / sizeof(tests[0])))
	{
		int c = tests[i];

		// Call both functions safely
		int ft = ft_isprint(c);
		int std = isprint((unsigned char)c);

		printf("  ft_isprint: %d\n", ft);
		printf("  isprint   : %d\n", std);

		if (ft == std)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
