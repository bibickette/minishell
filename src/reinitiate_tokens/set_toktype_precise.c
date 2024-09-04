/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_toktype_precise.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:13:30 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 15:45:05 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_type(t_token *current)
{
	if (is_builtin(current->str) == OK)
	{
		current->type = BUILTIN_TYPE;
		if (ft_strncmp(current->str, "echo", ft_strlen(current->str)) == 0)
			current->builtin_type = BUILT_W_OPT;
		if ((ft_strncmp(current->str, "env", ft_strlen(current->str)) == 0)
			|| (ft_strncmp(current->str, "pwd", ft_strlen(current->str)) == 0))
			current->builtin_type = BUILT_NO_OPT_ARG;
		else
			current->builtin_type = BUILT_NO_OPTION;
	}
}

void	reset_operator_type(t_token *current)
{
	if (check_operator(current->str) == OK)
	{
		if (current->str[0] == '|')
			current->type = PIPE_TYPE;
		else if (ft_strcmp(current->str, "<<") == 0)
			current->type = HERE_DOC_TYPE;
		else if (ft_strcmp(current->str, ">>") == 0)
			current->type = HD_APPEND_TYPE;
		else if (ft_strcmp(current->str, ">") == 0)
			current->type = OUT_REDIR_TYPE;
		else if (ft_strcmp(current->str, "<") == 0)
			current->type = IN_REDIR_TYPE;
	}
}
