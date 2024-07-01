/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:08:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/01 20:11:29 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_prompt_arg(char *prompt, t_data *minishell)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			i++;
		else if (prompt[i] == 34 || prompt [i] == 44)
		{
			if (have_twin(prompt, i, prompt[i], minishell) == OK)
				i += cpy_twin(prompt, i, prompt[i], minishell);
			else
				i += cpy_till_end(prompt, i, minishell);
		}
		else
			i += cpy_till_end(prompt, i, minishell);
	}
}
