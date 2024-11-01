/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:32:32 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:36:02 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	nb_is_prime(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	if ((nb == 2) || (nb == 3) || (nb == 2147483647))
		return (1);
	if (nb % 2 == 0)
		return (0);
	i = 3;
	while ((nb % i != 0) && (i * i <= nb))
		i += 2;
	if (nb % i == 0)
		return (0);
	return (1);
}
