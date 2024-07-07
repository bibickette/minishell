/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:08:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/07 16:56:08 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *prompt, t_list **token)
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
			ft_lstclear_custom(token, free);
			return (BUFF_OVERFLOW);
		}
		else if (*prompt_loop == 34 || *prompt_loop == 39)
		{
			handle_quote(&prompt_loop, token, buffer);
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
		if (*token == NULL)
		{
			*token = ft_lstnew_custom(buffer);
		}
		else
			ft_lstadd_back_libft(token, ft_lstnew_custom(buffer));
	}
	return (OK);
}
