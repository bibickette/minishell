/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:57:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/23 21:23:11 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	printf("Token: %d\n", token->index);
	printf("      str: %s\n", token->str);
	if (token->quote != N_QUOTE)
		printf("      quote: %d\n", token->quote);
	if (token->builtin_type != 0)
		printf("	builtin_type: %d\n", token->builtin_type);
	printf("      type: %d\n", token->type);
	printf("\n");
}

void	print_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	printf("T_CMD: %d\n", cmd->index);
	printf("      type: %d\n", cmd->cmd_type);
	printf("      cmd: %s\n", cmd->cmd);
	if (cmd->cmd_args)
		print_double_tab(cmd->cmd_args);
	printf("      nb_files: %d\n", cmd->nb_files);
	if (cmd->nb_files > 0)
		print_all_files(cmd->files);
	printf("\n");
}

void	print_all_files(t_file *files)
{
	int	i;

	i = -1;
	if (!files)
		return ;
	while (files[++i].name)
	{
		printf("file name : %s\n", files[i].name);
		printf("file index cmd : %d\n", files[i].index_cmd);
		printf("file type : %d\n", files[i].type);
		printf("file is open : %d\n", files[i].is_open);
		printf("file fd open : %d\n", files[i].fd);
	}
}
