/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 15:21:07 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	int		quote;
	t_list	*last;
	t_token	*content;

	quote = 0;
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(*prompt_loop) == OK)
	{
		quote = check_quote_type(prompt_loop);
		buffer = cpy_twin(prompt_loop, buffer);
		add_token(token, buffer);
		last = ft_lstlast(*token);
		content = last->content;
		content->quote = quote;
		ft_bzero(buffer, BSIZE);
	}
	else
		return (ft_putstr_fd(QUOTE_ERR, STDERR_FILENO), KO);
	return (OK);
}
