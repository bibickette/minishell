/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:58:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 18:04:01 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	t_token	*tmp;

	tmp = (t_token *)token;
	free(tmp->str);
	free(tmp);
}
