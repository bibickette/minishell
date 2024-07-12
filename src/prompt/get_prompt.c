/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 22:03:53 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	met le prompt dans la variable prompt
*/

char	*get_prompt(void)
{
	char	*prompt;

	prompt = NULL;
	prompt = get_next_line(STDIN_FILENO, 0);
	if (!prompt)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	return (prompt);
}
