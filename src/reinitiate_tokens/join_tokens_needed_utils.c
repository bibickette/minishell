/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens_needed_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:25:24 by phwang            #+#    #+#             */
/*   Updated: 2024/08/30 22:37:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_economy(char *new_prompt, char *tmp_brut)
{
	if (new_prompt[ft_strlen(tmp_brut)] != ' '
		&& new_prompt[ft_strlen(tmp_brut)] != '\0')
		return (OK);
	return (KO);
}

int	check_new_prompt(char *new_prompt, char *tmp_brut)
{
	if (new_prompt[0] == '|' || new_prompt[0] == '<' || new_prompt[0] == '>'
		|| new_prompt[ft_strlen(tmp_brut)] == '|'
		|| new_prompt[ft_strlen(tmp_brut)] == '>'
		|| new_prompt[ft_strlen(tmp_brut)] == '<')
		return (OK);
	return (KO);
}
