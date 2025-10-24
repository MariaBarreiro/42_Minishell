/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:58:38 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/26 11:09:08 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_ptr_len(uintptr_t content);
int	ft_print_ptr(unsigned long long content);

///Recursively output hexadecimal digits of 'content' in lowercase

void	ft_ptr_digits(uintptr_t content)
{
	if (content >= 16)
	{
		ft_ptr_digits(content / 16);
		ft_ptr_digits(content % 16);
	}
	else
	{
		if (content <= 9)
			ft_putchar_fd_printf((content + '0'), 1);
		else
			ft_putchar_fd_printf((content - 10 + 'a'), 1);
	}
}

///Calculate the number of hex digits for 'content'

int	ft_ptr_len(uintptr_t content)
{
	unsigned int	len;

	len = 0;
	while (content)
	{
		content /= 16;
		len++;
	}
	return (len);
}

///Print a pointer value with the prefix

int	ft_print_ptr(unsigned long long content)
{
	size_t			to_print;

	to_print = 0;
	if (!content)
	{
		to_print += write(1, "(nil)", 5);
		return (to_print);
	}
	to_print += write(1, "0x", 2);
	if (content == 0)
		to_print = write(1, "0", 1);
	else
	{
		ft_ptr_digits(content);
		to_print += ft_ptr_len(content);
	}
	return (to_print);
}
