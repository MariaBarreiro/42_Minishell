/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:56 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:44 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///s: the original string from which to create the substring;
///start: the starting index of the substring withing 's';
///len: the maximum length of the substring;
///RETURN: SUCCESS: pointer to the substring;
///RETURN: FAILURE: null;

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	k;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (0);
	k = ft_strlen(s);
	i = 0;
	j = start;
	if (j >= k)
		return (ft_strdup(""));
	if (len > (k - j))
		len = k - j;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (s[j] && i < len)
	{
		sub[i] = s[j];
		i++;
		j++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int	main()
{
	char const s[] = "42Porto!";
	unsigned int start = 3;
	printf("ft_substr: %s\n", ft_substr(s, start, 3)); 
	return (0);
}*/
