/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:46:28 by phwang            #+#    #+#             */
/*   Updated: 2024/06/12 19:19:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

int		create_cmd_bonus(t_pipex *pipex, int argc, char **argv);
int		get_cmds_bonus(int argc, char **argv, t_pipex *pipex);
void	handle_heredoc(char **argv);

#endif