/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:17:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 15:21:02 by phwang           ###   ########.fr       */
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
