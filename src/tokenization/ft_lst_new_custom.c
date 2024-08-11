/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:11:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 17:57:25 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_custom(char buffer[BSIZE])
{
	char		*dyna_buffer;
	t_token		*token;
	t_list		*new;

	dyna_buffer = ft_strdup(buffer);
	token = ft_calloc(1, sizeof(t_token));
	if (!dyna_buffer || !token)
		return (NULL);
	token->str = dyna_buffer;
	token->index = 0;
	new = ft_lstnew_libft(token);
	if (!new)
	{
		free(dyna_buffer);
		free(token);
	}
	return (new);
}
