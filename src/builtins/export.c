/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 23:48:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmd(char *var, t_data *minishell)
{
	int	i;
	int	y;

	// t_list	*new_export;
	// new_export = NULL;
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	y = -1;
	while (++y < i)
		if (var[y] == ' ')
			return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	if (export_replacement(minishell, &var) == OK)
		return (OK);
	else
	{
		char_add_back_tab(&minishell->builtins->env, var);
		// new_export = ft_lstnew_libft(ft_strdup(var));
		// if (!new_export)
		// 	return (ft_putstr_fd(LSTNEW_ERR, STDERR_FILENO), KO);
		// ft_lstadd_back_libft(export_head, new_export);
	}
	return (OK);
}

int	export_replacement(t_data *minishell, char **var)
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
			minishell->builtins->env[i] = ft_strdup(*var);
			free(tmp_var);
			if (!minishell->builtins->env[i])
				return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	free(tmp_var);
	return (KO);
}
/*
si la variable a export existe deja, remplace par la nouvelle valeur
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

/*
note sur env et export :
si la variable na pas	de = alors elle ne sera pas intégré dans env
elle le sera seulement dans export
export display "declare -x " avant chaque case de lenv

si la variable a		un = et rien apres alors elle est export dans env et export
elle est export dans export avec var=""

si le premier char cest =, renvoyer erreur ; ca fait un last status = 1

*/
