/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 09:25:53 by mda-enca          #+#    #+#             */
/*   Updated: 2025/05/10 09:26:20 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_case(va_list args, const char format);
int	ft_print_nbr(int content);
int	ft_print_char(int content);

int	ft_printf(const char *format, ...)
{
	size_t		i;
	va_list		args;
	int			total_len;

	i = 0;
	va_start(args, format);
	total_len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			total_len += ft_case(args, format[i + 1]);
			i++;
		}
		else if (format[i])
			total_len += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (total_len);
}

int	ft_case(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == '%')
		len += ft_print_char('%');
	else if (format == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	return (len);
}

int	ft_print_nbr(int content)
{
	char	*converted;
	int		len;

	converted = ft_itoa_printf(content);
	len = ft_print_str(converted);
	free(converted);
	return (len);
}

int	ft_print_char(int content)
{
	write (1, &content, 1);
	return (1);
}
