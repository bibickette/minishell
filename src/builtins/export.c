/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/08/25 14:03:28 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmd(t_list **export_head, char *var, t_data *minishell)
{
	t_list	*new_export;
	char	*exported;
	char	*tmp;

	exported = NULL;
	new_export = NULL;
	tmp = NULL;
	if (exporting(&tmp, var, &exported, minishell) == KO)
		return (KO);
	if (tmp)
		free(tmp);
	if (export_replacement(minishell, minishell->builtins->export, var,
			&exported) == OK)
		return (OK);
	else
	{
		new_export = ft_lstnew_libft(exported);
		if (!new_export)
			return (ft_putstr_fd(LSTNEW_ERR, STDERR_FILENO), KO);
		ft_lstadd_back_libft(export_head, new_export);
	}
	return (OK);
}

int	exporting(char **tmp, char *var, char **exported, t_data *minishell)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (export_check(tmp, var) == KO)
		return (KO); // if KO do nothing
	if (var[++i] == 39)
	{
		if (export_single_quote(exported, var, *tmp) == KO)
			return (KO);
	}
	else if (var[i] == 34)
	{
		if (export_double_quote(minishell, exported, *tmp, var) == KO)
			return (KO);
	}
	else if (export_no_quote(exported, var, *tmp) == KO)
		return (KO);
	return (OK);
}
/*
choisi lun des trois export dispo :
no quote
single quote
double quote
*/

int	export_no_quote(char **exported, char *var, char *tmp)
{
	int	y;

	*exported = ft_strdup(var);
	if (!*exported)
	{
		free(tmp);
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	}
	y = -1;
	while ((*exported)[++y])
		if ((*exported)[y] == ' ')
			(*exported)[y] = '\0';
	return (OK);
}
/*
build lexport de no quote
*/

int	export_single_quote(char **exported, char *var, char *tmp)
{
	int	i;
	int	y;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	*exported = ft_calloc(++i + ft_strlen(tmp) + 1, sizeof(char));
	if (!*exported)
	{
		free(tmp);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	y = -1;
	while (++y < i)
		(*exported)[y] = var[y];
	i = -1;
	while (tmp[++i])
		(*exported)[i + y] = tmp[i];
	(*exported)[y + i] = '\0';
	return (OK);
}
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