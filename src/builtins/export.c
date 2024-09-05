/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/05 23:42:21 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_cmd_no_arg(char **export)
{
	int i;
	i = -1;
	while(export[++i])
	{
		if (ft_strcmp(export[i], "") != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(export[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
}

int	export_cmd_w_arg(char *var, t_data *minishell)
{
	if (check_export_format(var, minishell) == KO)
		return (KO);
	if (has_equal(var) == OK)
	{
		if (export_replacement_env(&minishell->builtins->env, &var) == OK)
			minishell->last_status = 0;
		else if (char_add_back_tab(&minishell->builtins->env, var) == KO)
		{
			minishell->last_status = 1;
			return (KO);
		}
	}
	/*
	else
	{
		if (char_add_back_tab(&minishell->builtins->export, var) == KO)
		{
			minishell->last_status = 1;
			return (KO);
		}
	}
	*/
	return (OK);
}

/*
note sur env et export :
si la variable na pas	de = alors elle ne sera pas intégré dans env
elle le sera seulement dans export OK
export display "declare -x " avant chaque case de lenv OK

si la variable a un = et rien apres alors elle est export dans env et export
elle est export dans export avec var=""

si le premier char cest =, renvoyer erreur ; ca fait un last status = 1 ok

*/

int	check_export_format(char *var, t_data *minishell)
{
	int	i;
	int	y;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (var[0] == '=' || (var[0] >= '0' && var[0] <= '9'))
		return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	y = -1;
	while (++y < i)
		if (check_more_special_char(var[y]) == KO)
			return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	minishell->last_status = 1;
	return (OK);
}

int	export_replacement_env(char ***env_or_export, char **var)
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
	while ((*env_or_export)[++i])
	{
		if (ft_strncmp((*env_or_export)[i], tmp_var, ft_strlen(tmp_var)) == 0)
		{
			free((*env_or_export)[i]);
			(*env_or_export)[i] = ft_strdup(*var);
			free(tmp_var);
			if (!(*env_or_export)[i])
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

int	has_equal(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			return (OK);
	return (KO);
}
