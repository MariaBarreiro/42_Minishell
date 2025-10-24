/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:13:00 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/11 15:48:07 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h> ///SIZE_MAX

///ft_calloc: Alloc memory for an array of nmemb size bytes each and zero it;
///size_t nmemb: Number of elements;
///size_t size: Size of each element;
///RETURN: SUCESS: Pointer to the allocated memory;
///RETURN: FAILURE: Null;

///SIZE_MAX / size!! - Protection from int overflow;

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	to_alloc;
	int		*array;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	to_alloc = nmemb * size;
	array = (void *)malloc(to_alloc);
	if (!array)
		return (0);
	ft_bzero(array, to_alloc);
	return (array);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	size_t	nmemb = 4;
	size_t	size = sizeof(int);

	// Use ft_calloc and standard calloc
	void *ptr1 = ft_calloc(nmemb, size);
	void *ptr2 = calloc(nmemb, size);

	// Check if allocation succeeded
	if (!ptr1 || !ptr2)
	{
		printf("Allocation failed\n");
		return (1);
	}

	// Print first few bytes to verify zero-initialization
	printf("ft_calloc bytes: ");
	for (size_t i = 0; i < nmemb * size; i++)
		printf("%02x ", ((unsigned char *)ptr1)[i]);
	printf("\n");

	printf("calloc    bytes: ");
	for (size_t i = 0; i < nmemb * size; i++)
		printf("%02x ", ((unsigned char *)ptr2)[i]);
	printf("\n");

	// Compare the two allocations
	if (memcmp(ptr1, ptr2, nmemb * size) == 0)
		printf("MATCH: Memory is zeroed and identical\n");
	else
		printf("MISMATCH: Memory is different\n");

	// Free the memory to avoid leaks
	free(ptr1);
	free(ptr2);

	return 0;
}*/
