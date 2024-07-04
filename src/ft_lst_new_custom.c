/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_custom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:11:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/04 17:12:29 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_custom(char buffer[BSIZE])
{
	char		*dyna_buffer;
	t_data	*data;
	t_list	*new;

	dyna_buffer = ft_strdup(buffer);
	data = ft_calloc(1, sizeof(t_data));
	if (!dyna_buffer || !data)
		return (NULL);
	data->word = dyna_buffer;
	data->index = 0;
	new = ft_lstnew_libft(data);
	if (!new)
	{
		free(dyna_buffer);
		free(data);
	}
	return (new);
}
