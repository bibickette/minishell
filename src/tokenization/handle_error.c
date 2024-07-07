/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:22:14 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/04 17:24:13 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(int ret, char *prompt)
{
	(void)prompt;
	printf("Error: %d\n", ret);
}
