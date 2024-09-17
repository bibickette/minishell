/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/16 17:17:16 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *token, t_data *minishell)
{
	char	*prompt;

	handle_signals();
	prompt = NULL;
	display_intro();
	while (1)
	{
		prompt = get_prompt(&minishell);
		if (ft_strlen(prompt) > 0 && tokenize(prompt, &token) != KO)
			if (token)
				if (the_parser_set(token, minishell, prompt) == OK
					&& lf_spechar_list(minishell, token) == OK
					&& check_token_operator_order(token, minishell) == OK)
					the_execution(token, minishell);
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}

int	the_parser_set(t_list *token, t_data *minishell, char *prompt)
{
	if (dupplicate_list(token, &minishell->brut_list) == KO)
		return (KO);
	set_index_again(token, minishell->brut_list);
	if (expand_everything(minishell, token) == KO)
		return (KO);
	if (separate_if_needed(minishell, token) == KO)
		return (KO);
	if (start_join_token_if_needed(token, prompt, minishell->brut_list) == KO)
		return (KO);
	first_token_is_exit(prompt, minishell, token);
	set_token_type(token);
	reset_cmd_pipe(token);
	return (OK);
}

void	the_execution(t_list *token, t_data *minishell)
{
	if (take_all_files(minishell, token) == KO)
		return ;
	build_cmd_tab(minishell, token);
	if (minishell->nb_cmd == 1)
		execve_one_cmd(minishell, minishell->command_tab[0], token);
	else
		execve_pipe(minishell, minishell->command_tab, token);
	free_files_tab(minishell, minishell->files);
	free_double_char(&minishell->command_tab);
	handle_file_hd(minishell);
}

int	build_cmd_tab(t_data *minishell, t_list *token)
{
	char	**cmd_tab;
	int		i;
	t_list	*tmp;

	i = 0;
	cmd_tab = NULL;
	tmp = token;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == CMD_TYPE
			|| ((t_token *)tmp->content)->type == BUILTIN_TYPE
			|| ((t_token *)tmp->content)->type == OPT_TYPE
			|| ((t_token *)tmp->content)->type == ARG_TYPE)
			if (put_in_cmd_tab(tmp, &minishell->command_tab, i) == KO)
				return (KO);
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	minishell->nb_cmd = i + 1;
	return (OK);
}

int	put_in_cmd_tab(t_list *tmp, char ***cmd_tab, int i)
{
	if (!(*cmd_tab) || !(*cmd_tab)[i])
	{
		if (char_add_back_tab(cmd_tab, ((t_token *)tmp->content)->str) == KO)
			return (KO);
	}
	else if ((*cmd_tab)[i])
	{
		(*cmd_tab)[i] = strjoin_wfree((*cmd_tab)[i], " ");
		if (!cmd_tab[i])
			return (ft_putstr_fd(STRJOIN_ERR, STDOUT_FILENO), KO);
		(*cmd_tab)[i] = strjoin_wfree((*cmd_tab)[i],
				((t_token *)tmp->content)->str);
		if (!(*cmd_tab)[i])
			return (ft_putstr_fd(STRJOIN_ERR, STDOUT_FILENO), KO);
	}
	return (OK);
}
