/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:49:42 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 16:03:30 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_toupper: Converts a char to uppercase;
///int c: Char to convert;
///RETURN: char in uppercase;

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main()
{
	int	c = 'a';
	printf("ft_toupper: %d", ft_toupper(c));
	printf("toupper: %d", toupper(c));
	return (0);
}*/
