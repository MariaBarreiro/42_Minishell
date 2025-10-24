/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:39:04 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/26 07:32:37 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

char			*ft_strdup_printf(const char *s);
char			*ft_char(char *str, unsigned int nb, long int len);
unsigned int	ft_countdigits(int n);

char	*ft_itoa_printf(int n)
{
	long			nb;
	long int		len;
	char			*str;

	nb = n;
	len = ft_countdigits(n);
	if (nb == 0)
		return (ft_strdup_printf("0"));
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (nb < 0)
	{
		nb = -n;
		str[0] = '-';
	}
	str = ft_char(str, nb, (len - 1));
	str[len] = '\0';
	return (str);
}

unsigned int	ft_countdigits(int n)
{
	unsigned int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_char(char *str, unsigned int nb, long int len)
{
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

char	*ft_strdup_printf(const char *s)
{
	size_t	i;
	size_t	n;
	char	*dup;

	n = 0;
	i = ft_strlen_printf(s);
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (n < i)
	{
		dup[n] = s[n];
		n++;
	}
	dup[n] = '\0';
	return (dup);
}
