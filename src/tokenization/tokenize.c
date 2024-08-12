/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:08:31 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/12 15:49:14 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *prompt, t_list **token)
{
	int		i;
	char	*prompt_loop;
	char	buffer[BSIZE];

	i = 0;
	if (check_special_char(prompt) == KO)
		return (KO);
	ft_bzero(buffer, BSIZE);
	prompt_loop = prompt;
	while (*prompt_loop)
		if (process_char(&prompt_loop, token, buffer, &i) == KO)
			return (ft_lstclear_custom(token, free), KO);
	if (ft_strlen(buffer) > 0)
		add_token(token, buffer);
	set_token_type(*token);
	return (OK);
}

int	check_special_char(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (i > 0 && prompt[i - 1] && prompt[i - 1] != '$' && prompt[i] == '?')
			return (ft_putstr_fd(SPECIAL_CHAR_ERR, STDERR_FILENO), KO);
		if (prompt[i] == '~' || prompt[i] == '&' || prompt[i] == '`'
			|| prompt[i] == '[' || prompt[i] == ']' || prompt[i] == '{'
			|| prompt[i] == '}' || prompt[i] == '*' || prompt[i] == ';'
			|| prompt[i] == ':' || prompt[i] == '\\' || prompt[i] == '('
			|| prompt[i] == ')' )
			return (ft_putstr_fd(SPECIAL_CHAR_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}
