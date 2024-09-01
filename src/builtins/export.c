/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/01 22:44:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmd(t_list **export_head, char *var, t_data *minishell)
{
	t_list	*new_export;
	int		i;
	int		y;

	new_export = NULL;
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	y = -1;
	while (++y < i)
		if (var[y] == ' ')
			return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	if (export_replacement(minishell, minishell->builtins->export, &var) == OK)
		return (OK);
	else
	{
		new_export = ft_lstnew_libft(ft_strdup(var));
		if (!new_export)
			return (ft_putstr_fd(LSTNEW_ERR, STDERR_FILENO), KO);
		ft_lstadd_back_libft(export_head, new_export);
	}
	return (OK);
}

int	export_replacement(t_data *minishell, t_list *export_head, char **var)
{
	char	*tmp_var;
	int		i;

	i = -1;
	tmp_var = ft_strdup(*var);
	if (!tmp_var)
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	while (tmp_var[++i])
		if (tmp_var[i] == '=')
			break ;
	if (ft_strlen(tmp_var) != (size_t)i)
		tmp_var[i + 1] = '\0';
	i = -1;
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], tmp_var,
				ft_strlen(tmp_var)) == 0)
		{
			free(minishell->builtins->env[i]);
			minishell->builtins->env[i] = *var;
			free(tmp_var);
			if (!minishell->builtins->env[i])
				return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	return (export_replacement_list(export_head, var, tmp_var));
}
/*
si la variable a export existe deja, remplace par la nouvelle valeur
*/

int	export_replacement_list(t_list *export_head, char **var, char *tmp_var)
{
	t_list	*tmp;

	tmp = export_head;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, tmp_var, ft_strlen(tmp_var)) == 0)
		{
			free(((t_token *)tmp->content)->str);
			((t_token *)tmp->content)->str = *var;
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

/*
build lexoport de single quote
*/

/*
builtin export :
3 facons de le recevoir :
variable=value prout			NO QUOTE | out = variable=value
variable="value prout $USER"	SG QUOTE | out = variable=value prout paulinette
variable='value prout $USER'	DB QUOTE | out = variable=value prout $USER

si la variable existe deja, la value est remplacée par la nouvelle entrée
sinon, elle est ajoutée a la liste des exports
la recherche de la variable se fait dabord dans env, puis dans export


export_cmd : main cmd, is the builtin
 - check le format, renvoie erreur si ! des trois types
 - build la variable a export
 - check si la variable a export existe deja
 - si oui, la remplace
 - sinon, lajoute a la liste export

exporting : fait le lien entre le check du formatage de la variable a export
	et le choix de lexport a faire

export_check : check le format de la variable a export
	- check si la variable a un =
	- check si la variable a un quote, et si oui, si le quote est bien fermé

export_no_quote : build lexport de no quote

export_single_quote : build lexport de single quote

export_double_quote : build lexport de double quote
export_handle_dollar : gere les $ expansions
export_dollar_in_str : gere les $ expansions dans une string
build_the_export : build lexport final de double quote

export_replacement : check si la variable a export existe deja
	et la remplace par la nouvelle valeur
export_replacement_list : check si la variable a export existe deja
	et la remplace par la nouvelle valeur dans la liste export

*/