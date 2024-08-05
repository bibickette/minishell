/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/05 12:28:15 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	int		type;
	t_list		*last;
	t_token		*content;

	type = 0;
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(*prompt_loop) == OK)
	{
		type = check_type(prompt_loop);
		buffer = cpy_twin(prompt_loop, buffer);
		add_token(token, buffer);
		last = ft_lstlast(*token);
		content = last->content;
		content->type = type;
		ft_bzero(buffer, BSIZE);
	}
	else
	{
		ft_putstr_fd("error single quote\n", STDERR_FILENO);
		return (KO);
	}
	return (OK);
}
