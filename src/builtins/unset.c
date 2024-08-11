/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:55:56 by phwang            #+#    #+#             */
/*   Updated: 2024/08/12 01:20:24 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_builtin *builtins, char *var)
{
	int	i;

	i = -1;
	while (builtins->env[++i])
		if (ft_strncmp(builtins->env[i], var, ft_strlen(var)) == 0
			&& builtins->env[i][ft_strlen(var)] == '=')
			builtins->env[i][0] = '\0';
	unset_cmd_check_export(builtins, var);
}

void	unset_cmd_check_export(t_builtin *builtins, char *var)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = builtins->export;
	while (tmp)
	{
		tmp2 = ((char *)tmp->content);
		if (tmp2)
		{
			if (ft_strncmp(tmp2, var, ft_strlen(var)) == 0
				&& tmp2[ft_strlen(var)] == '=')
			{
				tmp->content = 0;
				return ;
			}
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}
