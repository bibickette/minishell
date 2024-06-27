/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:07:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 11:27:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenise_prompt(char **splited_prompt)
{
	if (!splited_prompt)
	{
		ft_putstr_fd("Error: tokenise_prompt failed\n", 2);
		return (NULL);
	}
	return (splited_prompt);
}
