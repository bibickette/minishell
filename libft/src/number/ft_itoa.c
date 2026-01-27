/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:06:20 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:26:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	size_nb(long int n)
{
	if (n / 10 == 0)
		return (1);
	return (1 + size_nb(n / 10));
}

static char	*fill_tab(char *tab, long int n, int size)
{
	if (n / 10 == 0)
	{
		if (n % 10 >= 0)
			tab[size] = (n % 10) + '0';
		else
			tab[size] = ((n % 10) * -1) + '0';
		return (tab);
	}
	if (n % 10 >= 0)
		tab[size] = (n % 10) + '0';
	else
		tab[size] = ((n % 10) * -1) + '0';
	return (fill_tab(tab, n / 10, size - 1));
}

char	*ft_itoa(int n)
{
	char		*nbtab;
	int			size;
	int			sign;
	long int	nb;

	nb = n;
	sign = 0;
	size = size_nb(nb);
	if (nb < 0)
		sign = 1;
	nbtab = malloc((size + sign + 1) * sizeof(char));
	if (!nbtab)
		return (NULL);
	if (sign == 1)
		nbtab[0] = '-';
	nbtab = fill_tab(nbtab, nb, size + sign - 1);
	nbtab[size + sign] = '\0';
	return (nbtab);
}
