/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:10:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/24 16:51:55 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	t_token	*last;

	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		last = ft_lstlast(*token)->content;
		if (last->str[0] == '-')
			last->type = OPT_TYPE;
		ft_bzero(buffer, BSIZE);
	}
	(*prompt_loop)++;
}
