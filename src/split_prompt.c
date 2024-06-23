/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:53:05 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 23:16:43 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_prompt(char *prompt)
{
	char	**split_prompt;

	if (!prompt)
	{
		ft_putstr_fd("Error: split_prompt failed\n", 2);
		return (NULL);
	}
	split_prompt = ft_split(prompt, ' ');
	if (!split_prompt)
	{
		ft_putstr_fd("Error: split_prompt failed\n", 2);
		return (NULL);
	}
	return (split_prompt);
}