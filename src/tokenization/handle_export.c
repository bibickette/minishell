/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:38:48 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/29 17:28:41 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_equal(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	printf("str[i] = %c\n", str[i]);
	if (str[i] == '=')
		return (1);
	return (0);
}

void	handle_export(t_list **token)
{
	t_list		*actual;
	t_token		*content;
	t_token		*next_content;
	char		*join;

	printf("beg\n");
	actual = *token;
	if (actual->content)
		content = actual->content;
	while (actual)
	{
		if (ft_strcmp(content->str, "export") == 0)
		{
			if (!actual->next)
				break ;
			actual = actual->next;
			content = actual->content;
			printf("export trouve\n");
			if (check_last_equal(content->str))
			{
				printf("egal trouve\n");
				next_content = actual->next->content;
				join = ft_strjoin(content->str, next_content->str);
				free(content->str);
				content->str = join;
				actual->next = suppr_element(&actual->next);
			}
		}
		if (!actual->next)
			break ;
		actual = actual->next;
		content = actual->content;
	}
	printf("end\n");
}
