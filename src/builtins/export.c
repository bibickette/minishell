/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 18:41:55 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd_no_arg(char **export)
{
	int	i;

	i = -1;
	while (export[++i])
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
	int		ret;
	char	*key_export;

	if (check_export_format(var, minishell) == KO)
		return (KO);
	if (has_equal(var) == OK)
	{
		ret = export_replacement_env(&minishell->builtins->env, &var);
		if (ret == M_KO)
		{
			minishell->last_status = 1;
			return (KO);
		}
		else if (ret == KO)
		{
			if (char_add_back_tab(&minishell->builtins->env, var) == KO)
			{
				minishell->last_status = 1;
				return (KO);
			}
			minishell->last_status = 0;
		}
		load_right_export(var, &key_export);
		ret = export_replacement_env(&minishell->builtins->export, &key_export);
		if (ret == M_KO)
		{
			free(key_export);
			minishell->last_status = 1;
			return (KO);
		}
		else if (ret == KO)
		{
			if (char_add_back_tab(&minishell->builtins->export,
					key_export) == KO)
			{
				free(key_export);
				minishell->last_status = 1;
				return (KO);
			}
			minishell->last_status = 0;
		}
		free(key_export);
		minishell->last_status = 0;
		return (OK);
	}
	else
	{
		load_right_export(var, &key_export);
		ret = export_replacement_env(&minishell->builtins->export, &key_export);
		if (ret == M_KO)
		{
			free(key_export);
			minishell->last_status = 1;
			return (KO);
		}
		else if (ret == KO)
		{
			if (char_add_back_tab(&minishell->builtins->export,
					key_export) == KO)
			{
				free(key_export);
				minishell->last_status = 1;
				return (KO);
			}
			minishell->last_status = 0;
		}
		free(key_export);
		minishell->last_status = 0;
		return (OK);
	}
	return (OK);
}
int	load_right_export(char *var, char **key_export)
{
	char	*value_export;
	int		i;

	value_export = NULL;
	*key_export = ft_strdup(var);
	if (has_equal(var) == OK)
	{
		i = -1;
		while ((*key_export)[++i])
			if ((*key_export)[i] == '=')
				break ;
		if (ft_strlen((*key_export)) != (size_t)i)
		{
			load_value_n_key_export(key_export, &value_export, &var);
			(*key_export) = strjoin_wfree((*key_export), value_export);
			free(value_export);
		}
		else
		{
			(*key_export) = ft_strjoin(var, "\"\"");
		}
	}
	return (OK);
}

/*
note sur env et export :
si la variable na pas	de = alors elle ne sera pas intégré dans env
elle le sera seulement dans export OK
export display "declare -x " avant chaque case de lenv OK

si la variable a		un = et rien apres alors elle est export dans env et export
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
	size_t	len_var;

	i = -1;
	tmp_var = ft_strdup(*var);
	if (!tmp_var)
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), M_KO);
	if (has_equal(tmp_var) == OK)
	{
		while (tmp_var[++i])
			if (tmp_var[i] == '=')
				break ;
		len_var = ft_strlen(tmp_var);
		if (len_var != (size_t)i)
			tmp_var[i + 1] = '\0';
	}
	i = -1;
	while ((*env_or_export)[++i])
	{
		if ((ft_strncmp((*env_or_export)[i], tmp_var, ft_strlen(tmp_var)) == 0
				|| (ft_strncmp((*env_or_export)[i], tmp_var,
						ft_strlen(tmp_var)) == 0
					&& ft_strlen((*env_or_export)[i]) == ft_strlen(tmp_var)))
			|| ((has_equal(tmp_var) == OK
					&& has_equal((*env_or_export)[i]) == OK
					&& ft_strncmp((*env_or_export)[i], tmp_var,
						ft_strlen(tmp_var)) == 0) || (has_equal(tmp_var) == KO
					&& ft_strlen(tmp_var) < ft_strlen((*env_or_export)[i])
					&& (*env_or_export)[i][ft_strlen(tmp_var)] == '='
					&& ft_strncmp((*env_or_export)[i], tmp_var,
						ft_strlen(tmp_var) + 1) == 0)
				|| ((has_equal((*env_or_export)[i]) == KO
						&& ft_strlen(tmp_var) > ft_strlen((*env_or_export)[i])
						&& tmp_var[ft_strlen((*env_or_export)[i])] == '='
						&& ft_strncmp((*env_or_export)[i], tmp_var,
							ft_strlen(tmp_var) - 1) == 0))))
		{
			free((*env_or_export)[i]);
			(*env_or_export)[i] = ft_strdup(*var);
			free(tmp_var);
			if (!(*env_or_export)[i])
				return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), M_KO);
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
