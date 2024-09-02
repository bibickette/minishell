/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:57:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 17:44:17 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	printf("Token: %d\n", token->index);
	printf("      str: %s\n", token->str);
	if (token->quote != N_QUOTE)
		printf("      quote: %d\n", token->quote);
	if (token->builtin_type != 0)
		printf("	builtin_type: %d\n", token->builtin_type);
	printf("      type: %d\n", token->type);
	printf("\n");
}
