/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:29:32 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:29:33 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
