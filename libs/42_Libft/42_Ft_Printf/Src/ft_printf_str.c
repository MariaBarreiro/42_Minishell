/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:59:45 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/26 11:00:30 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_print_str(char *content);

int	ft_put_str(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		write(1, &content[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_str(char *content)
{
	size_t	len;

	len = 0;
	if (!content)
	{
		len += ft_put_str("(null)");
		return ((int)len);
	}
	while (content[len])
	{
		ft_putchar_fd_printf(content[len], 1);
		len++;
	}
	return ((int)len);
}
