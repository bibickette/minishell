/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/08/12 01:42:20 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmd(t_list **export_head, char *var)
{
	int	i;

	if (has_equal(var) == KO)
		return (KO);
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (var[i + 1] == 34 || var[i + 1] == 39)
		if (var[ft_strlen(var) - 1] != var[i + 1])
			return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	// just checked for format = with no free quote
	ft_lstadd_back_libft(export_head, ft_lstnew_libft(var));
	return (OK);
}
/*
need dollar expansion handling
string quote handling
*/

int	has_equal(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			return (OK);
	return (KO);
}
