/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:39:01 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:36:10 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	power_nb(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	return (nb * power_nb(nb, power - 1));
}

/*int main()
{
	int nb = 2;
	int power = 5;
	__builtin_printf("%d", ft_recursive_factorial(nb, power));
}*/
