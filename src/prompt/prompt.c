/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 19:05:44 by yantoine         ###   ########.fr       */
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
		if (!prompt || ft_strcmp(prompt, "exit") == 0)
			handle_exit(minishell, prompt, token);
		else if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		else if (tokenize(prompt, &token) != KO)
		{
			expand_everything(minishell, token);
			join_token_if_needed(token, prompt);
			set_token_type(token);
			take_all_files(minishell, token);
			ft_lstiter(token, print_token);
			minishell->command_list = command_listing(token);
			set_entire_command(minishell->command_list);
			ft_lstiter(minishell->command_list, print_command);
			execution(minishell);
			free_files_tab(minishell, minishell->files);
			free_command_list(minishell->command_list);
		}
		ft_lstclear_custom(&token, free);
		free(prompt);
	}
}
void	join_token_if_needed(t_list *token, char *prompt)
{
	int i;
	int quote_nb;
	i = -1;
	t_list *tmp_head;
	tmp_head = token;
	int token_quote;
	token_quote = 0;
	while (tmp_head)
	{
		if(((t_token *)tmp_head->content)->quote != N_QUOTE)
		{
			token_quote++;
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	printf("nb de token w quote = %d\n", token_quote); 
	tmp_head = token;
	int j;
	int reset;
	reset = 0;
	int no_quote;
		quote_nb = 0;
		no_quote = 0;
	//donc en gros en dessous je join tous les chars avec char qui ont quote si besoin
	while(prompt[++i])
	{
	// chercher dans le prompt le x guillemet
		if(i == 0 && (prompt[i] == 34 || prompt[i] == 39))
			quote_nb++;
		if(prompt[i] == 34 || prompt[i] == 39)
		{
			if(i != 0)
				quote_nb++;
			if(i - 1 >= 0 && prompt[i - 1] != ' ' && quote_nb % 2 != 0)
			{
				printf("quote nb = %d\n", quote_nb / 2);
				 // chercher dans les tokens le quote / 2 guillemet
				j = -1;
				t_list *is_next_token;
				while(tmp_head)
				{
					if((t_token *)tmp_head->next && ((t_token *)tmp_head->next->content)->quote != N_QUOTE)
					{
						j++;
						if(j == (quote_nb / 2 - reset))
						{
							((t_token *)tmp_head->content)->quote = JOINED;
							is_next_token = tmp_head->next;
							printf("quote to join nb = %d\n", quote_nb / 2);
							printf("quote to join = %s\n", ((t_token *)is_next_token->content)->str);
							// ici on join, on est sur le token dapres = il faut join avec celui davant
							/*
							recuperer un pointeur sur ce token = celui dapres
							envoyer ce pointeur et le token davant a une fonction qui va strjoin les deux tokens
							*/
							join_token(token, is_next_token);
						i = -1;
						reset++; // remettre a la tete
							break ;
						}
					}
					if(tmp_head->next == NULL)
						break ;
					tmp_head = tmp_head->next;
				}
				if (tmp_head->next == NULL)
					break ;
				tmp_head = token;
			}
			// continue till other " or '
		}
	}
	//mnt je need de join les token qui ont quote avec ceux qui sont char collé
	
	// i = -1;
	// quote_nb = 0;
	// while(prompt[++i])
	// {
	// 	if (prompt[i] == 34 || prompt[i] == 39)
	// 	{
	
	// 		char quote_end;
	// 		int len_tmp;
	// 		len_tmp = -1;
	// 		quote_end = prompt[i];
	// 		while(prompt[++len_tmp + i])
	// 		{
	// 			if(prompt[len_tmp + i] == quote_end)
	// 			{
	// 				break ;
	// 			}
	// 		}
	// 		if(prompt[len_tmp + i + 1] != '\0' && prompt[len_tmp + i + 1] != ' ')
	// 		{
	// 			printf("pouet end quote and to join\n");
	// 			// la je suis sur la fin dla quote
	// 			//
	// 		}
	// 	}
		
	// }
	
	// tmp_head = token;
	// while(tmp_head)
	// {
	// 	printf("token = %s\n", ((t_token *)tmp_head->content)->str);
	// 	if (tmp_head->next == NULL)
	// 		break ;
	// 	tmp_head = tmp_head->next;
	// }
	// regarder si le char davant est un espace
	// si non, chercher dans les tokens le x guillemet
	// regarder si le token davant x existe avec x > 0
	// strjoin les deux tokens
	// supprimer le token x
	
}

void join_token(t_list *token, t_list *is_next_token)
{
	t_list *tmp_head;
	t_list *next_tmp;
	
	tmp_head = token;
	while(tmp_head)
	{
		if(tmp_head->next == is_next_token)
		{
			printf("on a trouve le token avant cest = %s\n", ((t_token *)tmp_head->content)->str);
			((t_token *)tmp_head->content)->str = strjoin_wfree(((t_token *)tmp_head->content)->str, ((t_token *)is_next_token->content)->str);
			if(is_next_token->next == NULL)
			{
				free(((t_token *)is_next_token->content)->str);
				free(is_next_token->content);
				free(is_next_token);
				tmp_head->next = NULL;
				// break ;
			}
			else
			{

				next_tmp = is_next_token->next;
				tmp_head->next = next_tmp;
				free(((t_token *)is_next_token->content)->str);
				free(is_next_token->content);
				free(is_next_token);
				// break ;
			}
			printf("mnt cest  %s\n", ((t_token *)tmp_head->content)->str);
			printf("quote type = %d\n", ((t_token *)tmp_head->content)->quote);
			// break ;
			// on a le token dapres
			// on strjoin les deux
			// on supprime le token dapres
			// on remet a jour le token avant
			// on remet a jour le token dapres
			// on remet a jour le token
			// on sort de la boucle
			// on free le token dapres
			// on free le token avant
			// on free le token
			// on sort de la fonction
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
}
