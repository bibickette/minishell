/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:57:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 18:00:46 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	ft_putstr_fd("Token: ", 1);
	ft_putstr_fd(token->str, 1);
	ft_putstr_fd("\n", 1);
}
