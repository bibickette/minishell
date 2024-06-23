/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 14:49:35 by yantoine         ###   ########.fr       */
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
	return (prompt);
}
