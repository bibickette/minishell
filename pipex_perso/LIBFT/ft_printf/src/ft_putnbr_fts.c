/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 02:03:11 by phwang            #+#    #+#             */
/*   Updated: 2023/12/04 16:46:28 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putnbr_len(int n, int *len)
{
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_len('-', len);
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr_len(nbr / 10, len);
		ft_putnbr_len(nbr % 10, len);
	}
	else
		ft_putchar_len(nbr + '0', len);
}

void	ft_putnbr_base(unsigned int n, char *base, int *len)
{
	unsigned long int	nbr;
	unsigned int		len_base;

	nbr = n;
	len_base = ft_lilstrlen(base);
	if (nbr > (len_base - 1))
	{
		ft_putnbr_base(nbr / len_base, base, len);
		ft_putnbr_base(nbr % len_base, base, len);
	}
	else
		ft_putchar_len(base[nbr], len);
}

void	ft_putnbr_ptr(unsigned long n, char *base, int *len)
{
	unsigned long int	nbr;
	unsigned int		len_base;

	nbr = n;
	len_base = ft_lilstrlen(base);
	if (nbr > (len_base - 1))
	{
		ft_putnbr_ptr(nbr / len_base, base, len);
		ft_putnbr_ptr(nbr % len_base, base, len);
	}
	else
		ft_putchar_len(base[nbr], len);
}

void	ft_putptr(unsigned long n, char *base, int *len)
{
	if (n == 0)
	{
		ft_putstr_len("(nil)", len);
		return ;
	}
	ft_putstr_len("0x", len);
	ft_putnbr_ptr(n, base, len);
}
