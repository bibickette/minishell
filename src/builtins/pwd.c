/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:40:09 by phwang            #+#    #+#             */
/*   Updated: 2024/08/12 01:34:32 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_builtin *builtins)
{
	if (builtins->pwd)
		free(builtins->pwd);
	builtins->pwd = getcwd(NULL, 0);
	if (!builtins->pwd)
		return (perror(PWD_ERR));
	ft_putstr_fd(builtins->pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/*
marche avec env -i ./minishell, est independant de l'env
*/