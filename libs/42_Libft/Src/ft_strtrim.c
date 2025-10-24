/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:44:45 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/12 14:45:46 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///s1: String to be trimmed;
///set: The string containing the set of characters to be removed;
///RETURN: SUCCESS: Trimmed string;
///RETURN: FAILURE: Null;

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;

	if (!s1)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	if (!set)
		return (ft_strdup(s1));
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[start] && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, (end - start + 1)));
}
/*
#include <stdio.h>

int	main()
{
	char const s1[] = "+++42Porto+++";
	char const set[] = "+";
	printf("ft_strtrim: %s\n", ft_strtrim(s1, set));
	return (0);
}*/
