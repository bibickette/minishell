/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/28 18:55:42 by phwang           ###   ########.fr       */
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
					if (has_multiple_dollar(expanded_exported[y]) == OK)
					{
						// step 1 : sep les $ dans un tab
						char **dollar_tab;
						dollar_tab = ft_split(expanded_exported[y], '$');
						if(!dollar_tab || !dollar_tab[0])
						{
							free(expanded_exported[y]);
							expanded_exported[y] = ft_strdup("");
						}
						else
						{
							char *tmp_expanded;
							char *tmp;
							if (expanded_exported[y][0] == '$')
							{
								char *add_first_dol;
								add_first_dol = ft_strdup("$");
								add_first_dol = strjoin_wfree(add_first_dol, dollar_tab[0]);
								tmp_expanded = dollar_expansion(add_first_dol, D_QUOTE, minishell);
								if (!tmp_expanded)
									tmp_expanded = ft_strdup("");
								free(add_first_dol);
								free(dollar_tab[0]);
								dollar_tab[0] = ft_strdup(tmp_expanded);
								free(tmp_expanded);
							}
							int i;
							i = 0;
							while(dollar_tab[++i])
							{
								tmp = ft_strdup("$");
								tmp = strjoin_wfree(tmp, dollar_tab[i]);
								tmp_expanded = dollar_expansion(tmp, D_QUOTE, minishell);
								free(tmp);
								free(dollar_tab[i]);
								dollar_tab[i] = ft_strdup(tmp_expanded);
								free(tmp_expanded);
							}
						}
						int z;
						// step 2 : rajouter les $ au debut des tab
						// step 3 : extand
						// step 4 : tout rassembler
						free(expanded_exported[y]);
						z = -1;
						expanded_exported[y] = ft_strdup("");
						while(dollar_tab[++z])
						{
							expanded_exported[y] = strjoin_wfree(expanded_exported[y], dollar_tab[z]);
						}
						free_double_char(dollar_tab);
						printf("----------------\n");				
						printf("expanded_exported[%d]: %s\n", y, expanded_exported[y]);
						printf("----------------\n");
						// end multiple dollar
					}
					else
					{
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
					}
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
			((t_token *)tmp_head->content)->str = ft_strdup(str_expanded);
			free(str_expanded);	
		}
		if(tmp_head->next == NULL)
			break;
		tmp_head = tmp_head->next;
	}
}
