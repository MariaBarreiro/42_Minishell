/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:10:48 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/11 12:59:22 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_atoi: Converts the initial portion of the str pointed to by nptr to int;
///const char *nptr: Str to convert;
///RETURN: SUCCESS: Converted value;

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		result;
	int		sign;

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
/*
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	const char *tests[] = {
		"0",
		"42",
		"-42",
		"+42",
		"   \t\n\r\v\f123",
		"   -987",
		"  +00123",
		"123abc",          // Stops parsing at non-digit
		"-+42",            // Invalid, sign error
		"--42",            // Invalid, sign error
		"",                // Empty string
		"    ",            // Only spaces
		"  - 42",          // Invalid format
		"+-123",           // Invalid format
		"2147483647",      // INT_MAX
		"-2147483648",     // INT_MIN
		"2147483648",      // Overflow
		"-2147483649",     // Underflow
		"0000000000000042", // Leading zeroes
		"   +000000",       // Just zero with signs
		"\t\n\v\f\r -42",
	};

	int count = sizeof(tests) / sizeof(tests[0]);
	int i = 0;
	while (i < count)
	{
		int ft = ft_atoi(tests[i]);
		int std = atoi(tests[i]);
		printf("ft_atoi: %d\n", ft);
		printf("atoi:    %d\n", std);
		printf("--------------------------------------\n");
		i++;
	}
	return 0;
}*/
