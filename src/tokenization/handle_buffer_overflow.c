/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buffer_overflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:02:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 21:52:25 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_buffer_overflow(t_list **token)
{
	ft_putstr_fd("Error: buffer overflow\n", STDERR_FILENO);
	ft_lstclear_custom(token, free);
	return (BUFF_OVERFLOW);
}
