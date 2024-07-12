/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_intro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:47:45 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 17:58:15 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_intro(void)
{
	ft_putstr_fd("  __  .__               _______", STDOUT_FILENO);
	ft_putstr_fd("__.__           .__  .__\n", STDOUT_FILENO);
	ft_putstr_fd("_/  |_|__| ____ ___.__./   ", STDOUT_FILENO);
	ft_putstr_fd("_____/|  |__   ____ |  | |  |\n", STDOUT_FILENO);
	ft_putstr_fd("\\   __\\  |/    <   |  |\\___", STDOUT_FILENO);
	ft_putstr_fd("__  \\ |  |  \\_/ __ \\|  | |  |\n", STDOUT_FILENO);
	ft_putstr_fd(" |  | |  |   |  \\___  |/        ", STDOUT_FILENO);
	ft_putstr_fd("\\|   Y  \\  ___/|  |_|  |__\n", STDOUT_FILENO);
	ft_putstr_fd(" |__| |__|___|  / ____/_______  ", STDOUT_FILENO);
	ft_putstr_fd("/|___|  /\\___  >____/____/\n", STDOUT_FILENO);
	ft_putstr_fd("              \\/\\/            ", STDOUT_FILENO);
	ft_putstr_fd("\\/      \\/     \\/\n", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_putstr_fd("            ", STDOUT_FILENO);
	ft_putstr_fd("Bienvenue dans minishell bebe !\n\n", STDOUT_FILENO);
}
