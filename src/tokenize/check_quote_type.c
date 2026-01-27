/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:17:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/12 15:42:54 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_type(char **prompt_loop)
{
	if (**prompt_loop == 34)
		return (D_QUOTE);
	else if (**prompt_loop == 39)
		return (S_QUOTE);
	return (0);
}
