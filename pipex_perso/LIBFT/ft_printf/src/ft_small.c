/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_small.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:08:21 by phwang            #+#    #+#             */
/*   Updated: 2023/12/12 15:14:10 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putchar_len(char c, int *len)
{
	*len += 1;
	write(1, &c, 1);
}

void	ft_putstr_len(char *s, int *len)
{
	if (!s)
		ft_putstr_len("(null)", len);
	else
	{
		*len += ft_lilstrlen(s);
		write(1, s, ft_lilstrlen(s));
	}
}

unsigned int	ft_lilstrlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
