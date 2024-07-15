/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:57:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/15 14:54:31 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	printf("Token str: %s\nToken type: %d\n", token->str, token->type);
}
