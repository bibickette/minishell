/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:10:30 by phwang            #+#    #+#             */
/*   Updated: 2024/01/25 19:29:29 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	var_print(va_list list_arg, const char **str, int *len)
{
	char	*upbase;
	char	*lowbase;
	char	*lilbase;

	upbase = "0123456789ABCDEF";
	lowbase = "0123456789abcdef";
	lilbase = "0123456789";
	(*str)++;
	if (**str == 'i' || **str == 'd')
		ft_putnbr_len(va_arg(list_arg, int), len);
	else if (**str == 'c')
		ft_putchar_len(va_arg(list_arg, int), len);
	else if (**str == '%')
		ft_putchar_len('%', len);
	else if (**str == 's')
		ft_putstr_len(va_arg(list_arg, char *), len);
	else if (**str == 'X')
		ft_putnbr_base((va_arg(list_arg, unsigned int)), upbase, len);
	else if (**str == 'x')
		ft_putnbr_base((va_arg(list_arg, unsigned int)), lowbase, len);
	else if (**str == 'u')
		ft_putnbr_base((va_arg(list_arg, unsigned int)), lilbase, len);
	else if (**str == 'p')
		ft_putptr((va_arg(list_arg, unsigned long)), lowbase, len);
}

int	ft_printf(const char *str, ...)
{
	va_list	list_arg;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	va_start(list_arg, str);
	while (*str)
	{
		if (*str == '%')
			var_print(list_arg, &str, &len);
		else
			ft_putchar_len(*str, &len);
		str++;
	}
	va_end(list_arg);
	return (len);
}
