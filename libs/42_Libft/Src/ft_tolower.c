/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:09:35 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 16:09:40 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_tolower: Converts a char to lowercase;
///int c: Char to convert;
///RETURN: Char in lowercase;

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main()
{
	int	c = 'A';
	printf("ft_tolower: %d\n", ft_tolower(c));
	printf("tolower: %d", tolower(c));
	return (0);
}*/
