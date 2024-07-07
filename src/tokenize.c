/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:08:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/07 15:31:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *prompt, t_list **minishell)
{
	int			i;
	char		*prompt_loop;
	char		buffer[BSIZE];

	i = 0;
	ft_bzero(buffer, BSIZE);
	prompt_loop = prompt;
	while (*prompt_loop)
	{
		if (i == BSIZE)
		{
			printf("Error: buffer overflow\n");
			ft_lstclear_custom(minishell, free);
			return (BUFF_OVERFLOW);
		}
		else if (*prompt_loop == 34 || *prompt_loop == 39)
		{
			handle_quote(&prompt_loop, minishell, buffer);
			i = 0;
		}
		else
		{
			buffer[i] = *prompt_loop;
			i++;
			prompt_loop++;
		}
	}
	if (ft_strlen(buffer) > 0)
	{
		if (*minishell == NULL)
		{
			*minishell = ft_lstnew_custom(buffer);
		}
		else
			ft_lstadd_back_libft(minishell, ft_lstnew_custom(buffer));
	}
	return (OK);
}
