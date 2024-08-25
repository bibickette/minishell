/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/25 17:44:02 by phwang           ###   ########.fr       */
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
		if (ft_strcmp(prompt, "exit") == 0)
			handle_exit(minishell, prompt, token);
		if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		tokenize(prompt, &token);
		set_token_type(token);
		expand_everything(minishell, token);
		ft_lstiter(token, print_token);
		minishell->command_list = command_listing(token);
		ft_lstiter(minishell->command_list, print_command);
		printf("la commande s'execute ICI\n");
		free_command_list(minishell->command_list);
		ft_lstclear_custom(&token, free);
		free(prompt);
	}
}

void expand_everything(t_data *minishell, t_list *token)
{
	t_list *tmp_head;

	tmp_head = token;
	while(tmp_head)
	{
		if(((t_token *)tmp_head->content)->quote != S_QUOTE)
		{
			char *str_expanded;
			char	**expanded_exported;
			str_expanded = ft_strdup(((t_token *)tmp_head->content)->str);
			if(!str_expanded)
				return(ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO));
			expanded_exported = ft_split(str_expanded, ' ');
			if (!expanded_exported)
				return(ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO));
			// au dessus, separe la string dans des tabs, copie loriginal du token
			char	*dollar;
			int		y;
			int i;
			y = -1;
			i = -1;
			while(expanded_exported[++y])
			{
				if (expanded_exported[y][0] == '$' && has_multiple_dollar(expanded_exported[y]) == KO)
				{
					dollar = ft_strdup(expanded_exported[y]);
					free(expanded_exported[y]);
					expanded_exported[y] = dollar_expansion(dollar, D_QUOTE, minishell);
					free(dollar);
				}
				else if (has_dollar(expanded_exported[y]) == OK)
				{
					// if (has_multiple_dollar(expanded_exported[y]) == OK)
					// {
					// 	char **multiple_dollar;
					// 	int dol;
					// 	dol = 0;
					// 	while(expanded_exported[y][++i])
					// 		if(expanded_exported[y][i] == '$')
					// 			dol++;
					// 	printf("gros pouet---------\n");
					// }
					// else
					// {
						char	*dup;
						while (expanded_exported[y][++i])
							if (expanded_exported[y][i] == '$')
								break ;
						dup = ft_strdup(expanded_exported[y] + i);
						dollar = dollar_expansion(dup, D_QUOTE, minishell);
						free(dup);
						if(!dollar)
							printf("prout\n");
						if (dollar[0])
						{
							expanded_exported[y][i] = '\0';
							expanded_exported[y] = strjoin_wfree(expanded_exported[y], dollar);
						}
						free(dollar);
					// }
				}
				expanded_exported[y] = strjoin_wfree(expanded_exported[y], " ");
			}
			// au dessus, gere les $ expansions, rajoute espace a la fin de chaque tab
			y = -1;
			free(str_expanded);
			str_expanded = 0;
			while (expanded_exported[++y])
			{
				str_expanded = strjoin_wfree(str_expanded, expanded_exported[y]);
			}
			free_double_char(expanded_exported);
			if(str_expanded[ft_strlen(str_expanded) - 1] == ' ')
				str_expanded[ft_strlen(str_expanded) - 1] = '\0';
			free(((t_token *)tmp_head->content)->str);
			printf("str_expanded: %s\n", str_expanded);
			((t_token *)tmp_head->content)->str = ft_strdup(str_expanded);
			free(str_expanded);	
		}
		if(tmp_head->next == NULL)
			break;
		tmp_head = tmp_head->next;
	}
}
