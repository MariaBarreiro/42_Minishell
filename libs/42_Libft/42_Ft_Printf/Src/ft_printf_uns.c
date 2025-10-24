/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:28:53 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/26 11:09:56 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_unsigned_len(unsigned int content);
int	ft_print_unsigned(unsigned int content);

char	*ft_unsigned_to_str(unsigned int content)
{
	unsigned int	len;
	char			*str_converted;

	str_converted = NULL;
	len = 0;
	len = ft_unsigned_len(content);
	str_converted = (char *)malloc((len + 1) * sizeof(char));
	if (!str_converted)
		return (NULL);
	str_converted[len] = 0;
	while (content != 0)
	{
		str_converted[len - 1] = (content % 10) + '0';
		content /= 10;
		len--;
	}
	return (str_converted);
}

int	ft_unsigned_len(unsigned int content)
{
	unsigned int	length;

	length = 0;
	while (content != 0)
	{
		content /= 10;
		length++;
	}
	return (length);
}

int	ft_print_unsigned(unsigned int content)
{
	char			*str_converted;
	unsigned int	len;

	str_converted = ft_unsigned_to_str(content);
	len = 0;
	if (content == 0)
		len += write (1, "0", 1);
	else
		len += ft_print_str(str_converted);
	return (free(str_converted), len);
}
