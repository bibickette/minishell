/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:36:54 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/30 19:01:05 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pair_quote(char *prompt)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (prompt[i])
	{
		if (prompt[i] == "'")
			squote++;
		if (prompt[i] == 34)
			dquote++;
		i++;
	}
	return(quote);
}
