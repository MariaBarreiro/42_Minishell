/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:27:52 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/26 11:06:29 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_hex_len(unsigned int content);
int	ft_print_hex(unsigned int content, const char format);

///Recursively output hexadecimal digits of 'content' using lowercase (x) 
///		or uppercase (X);

void	ft_hex_digits(unsigned int content, const char format)
{
	if (content >= 16)
	{
		ft_hex_digits(content / 16, format);
		ft_hex_digits(content % 16, format);
	}
	else
	{
		if (content <= 9)
		{
			ft_putchar_fd_printf((content + '0'), 1);
		}
		if (content > 9 && content <= 16)
		{
			if (format == 'x')
				ft_putchar_fd_printf(((content - 10) + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd_printf(((content - 10) + 'A'), 1);
		}
	}
}

///Return the number of hexadecimal digits required to represent the 
///		'content';

int	ft_hex_len(unsigned int content)
{
	unsigned int	length;

	length = 0;
	while (content != 0)
	{
		content /= 16;
		length++;
	}
	return (length);
}

int	ft_print_hex(unsigned int content, const char format)
{
	unsigned int	len;

	len = 0;
	if (content == 0)
		return (write(1, "0", 1));
	else
		ft_hex_digits(content, format);
	len = ft_hex_len(content);
	return (len);
}
