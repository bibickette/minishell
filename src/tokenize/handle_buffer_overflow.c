/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buffer_overflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:02:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/05 23:37:34 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_buffer_overflow(t_list **token)
{
	ft_putstr_fd(BUFFER_ERR, STDERR_FILENO);
	ft_lstclear_custom(token, free);
	return (BUFF_OVERFLOW);
}
