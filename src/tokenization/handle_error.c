/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:22:14 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 22:09:53 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(int ret, char *prompt)
{
	char *ret_nb;

	(void)prompt;
	ret_nb = ft_itoa(ret);
	ft_putstr_fd(HANDLE_ERROR, STDERR_FILENO);
	ft_putstr_fd(ret_nb, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(ret_nb);
}
