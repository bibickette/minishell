/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buffer_overflow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:02:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 18:00:30 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_buffer_overflow(t_list **token)
{
	printf("Error: buffer overflow\n");
	ft_lstclear_custom(token, free);
	return (BUFF_OVERFLOW);
}
