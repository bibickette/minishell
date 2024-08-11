/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:02 by phwang            #+#    #+#             */
/*   Updated: 2024/08/11 18:47:44 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type_operator(t_token *last_token)
{
	if (last_token->str[0] == '|')
		last_token->type = PIPE_TYPE;
	else if (ft_strcmp(last_token->str, "<<") == 0)
		last_token->type = HERE_DOC_TYPE;
	else if (ft_strcmp(last_token->str, ">>") == 0)
		last_token->type = HD_APPEND_TYPE;
	else if (ft_strcmp(last_token->str, ">") == 0)
		last_token->type = OUT_REDIR_TYPE;
	else if (ft_strcmp(last_token->str, "<") == 0)
		last_token->type = IN_REDIR_TYPE;
}
