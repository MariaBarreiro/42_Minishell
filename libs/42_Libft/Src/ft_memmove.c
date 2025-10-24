/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:51 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 13:23:05 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_memmove: Moves n bytes from memory area src to memory area dest;
///void *dest: Pointer to the destination memory area;
///const void *src: Pointer to the source memory area;
///size_t n: Number of bytes to be copied;
///RETURN: SUCCESS: Dest;

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (src > dest || dest >= (src + n))
		return (ft_memcpy(dest, src, n));
	else if (src < dest)
	{
		while (n)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char cases[][32] = {
		"1234567890",       // Normal move
		"abcdef",           // Overlap forward
		"abcdef",           // Overlap backward
		"abcdef",           // Full move
		"",                 // Empty string
		"abc\0def",         // With null inside
	};

	size_t offsets_src[] = {0, 0, 2, 0, 0, 0};
	size_t offsets_dst[] = {3, 2, 0, 0, 0, 0};
	size_t sizes[]       = {5, 4, 4, 6, 0, 7};

	int count = sizeof(sizes) / sizeof(sizes[0]);
	int i = 0;

	while (i < count)
	{
		char std_buf[32];
		char ft_buf[32];

		// Copy test string to both buffers
		strcpy(std_buf, cases[i]);
		strcpy(ft_buf, cases[i]);

		// Get source and destination pointers with offsets
		void *std_dst = std_buf + offsets_dst[i];
		void *std_src = std_buf + offsets_src[i];
		void *ft_dst = ft_buf + offsets_dst[i];
		void *ft_src = ft_buf + offsets_src[i];

		// Apply memmove and ft_memmove
		memmove(std_dst, std_src, sizes[i]);
		ft_memmove(ft_dst, ft_src, sizes[i]);

		printf("After memmove   : \"%s\"\n", std_buf);
		printf("After ft_memmove: \"%s\"\n", ft_buf);

		if (memcmp(std_buf, ft_buf, 32) == 0)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
