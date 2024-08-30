/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:45:16 by phwang            #+#    #+#             */
/*   Updated: 2024/08/15 17:31:18 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_replacement(t_data *minishell, t_list *export_head, char *var,
		char **exported)
{
	char	*tmp_var;
	int		i;

	i = -1;
	tmp_var = ft_strdup(var);
	while (tmp_var[++i])
		if (tmp_var[i] == '=')
			break ;
	tmp_var[i + 1] = '\0';
	i = -1;
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], tmp_var,
				ft_strlen(tmp_var)) == 0
			&& minishell->builtins->env[i][ft_strlen(tmp_var) - 1] == '=')
		{
			free(minishell->builtins->env[i]);
			minishell->builtins->env[i] = *exported;
			free(tmp_var);
			if (!minishell->builtins->env[i])
				return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	return (export_replacement_list(export_head, exported, tmp_var));
}
/*
si la variable a export existe deja, remplace par la nouvelle valeur
*/

int	export_replacement_list(t_list *export_head, char **exported, char *tmp_var)
{
	t_list	*tmp;

	tmp = export_head;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, tmp_var, ft_strlen(tmp_var)) == 0
			&& ((char *)tmp->content)[ft_strlen(tmp_var) - 1] == '=')
		{
			free(tmp->content);
			tmp->content = (void *)*exported;
			return (free(tmp_var), OK);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	free(tmp_var);
	return (KO);
}
/*
si la variable a export existe deja,
	remplace par la nouvelle valeur dans la liste export
*/
