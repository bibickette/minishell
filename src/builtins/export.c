/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:10:29 by phwang            #+#    #+#             */
/*   Updated: 2024/08/15 16:02:10 by phwang           ###   ########.fr       */
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
	if(exporting(&tmp, var, &exported, minishell) == KO)
		return (KO);
	printf("tmp: %s\n", tmp);
	printf("exported: %s\n", exported);
	if (tmp)
		free(tmp);
	// if
	// verifier si la variable existe, si elle existe, remplacer le content par ce nouveau content
	// else
	if (expansion_exist(minishell, var) == OK)
		return (expansion_replacement(minishell, var, &exported));
	else
	{	
		new_export = ft_lstnew_libft(exported);
		if (!new_export)
			return (ft_putstr_fd(LSTNEW_ERR, STDERR_FILENO), KO);
		ft_lstadd_back_libft(export_head, new_export);
	}
	return (OK);
}
/*
need dollar expansion handling
string quote handling

si no quote : il faut juste envoyer tout ce quil y a de coller apres =
si single quote : renvoyer tout le contenu du single quote SANS les quotes
si double quote  : renvoyer le contenu sans les quotes avec les $expanded

si la var existe deja alors faut remplacer la suite -> pas fait encore

*/
int expansion_exist(t_data *minishell, char *var)
{
	t_list *tmp;
	char *tmp_var;
	int i;

	i = -1;
	
	tmp_var = ft_strdup(var);
	while (tmp_var[++i])
		if (tmp_var[i] == '=')
			break ;
	tmp_var[i + 1] = '\0';
	i = -1;
	while (minishell->builtins->env[++i])
		if (ft_strncmp(minishell->builtins->env[i], tmp_var, ft_strlen(tmp_var)) == 0
			&& minishell->builtins->env[i][ft_strlen(tmp_var) - 1] == '=')
			return(free(tmp_var), OK);
	tmp = minishell->builtins->export;
	while(tmp)
	{
		if(ft_strncmp((char *)tmp->content, tmp_var, ft_strlen(tmp_var)) == 0
			&& ((char *)tmp->content)[ft_strlen(tmp_var) - 1] == '=')
			return(free(tmp_var), OK);
		if(tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	free(tmp_var);
	return (KO);
}

int expansion_replacement(t_data *minishell, char *var, char **exported)
{
	t_list *tmp;
	char *tmp_var;
	int i;

	i = -1;
	tmp_var = ft_strdup(var);
	while (tmp_var[++i])
		if (tmp_var[i] == '=')
			break ;
	tmp_var[i + 1] = '\0';
	i = -1;
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], tmp_var, ft_strlen(tmp_var)) == 0
			&& minishell->builtins->env[i][ft_strlen(tmp_var) - 1] == '=')
		{
			free(minishell->builtins->env[i]);
			minishell->builtins->env[i] = *exported;
			if (!minishell->builtins->env[i])
				return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
		}
	}
	// exp_tmp = NULL;
	tmp = minishell->builtins->export;
	while(tmp)
	{
		// *exp_tmp = ((char *)tmp->content);
		if(ft_strncmp((char *)tmp->content, tmp_var, ft_strlen(tmp_var)) == 0
			&& ((char *)tmp->content)[ft_strlen(tmp_var) - 1] == '=')
		{
			free(tmp->content);
			tmp->content = (void *)*exported;
		}
		if(tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	free(tmp_var);
	return (OK);
}

int exporting(char **tmp, char *var, char **exported, t_data *minishell)
{
	int i;
	
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if(export_check(tmp, var) == KO)
		return (KO);
	if (var[++i] == 39) // single quote
	{
		if (export_single_quote(exported, var, *tmp) == KO)
			return (KO);
	}
	else if (var[i] == 34) // double quote
	{
		if (export_double_quote(minishell, exported, *tmp, var) == KO)
			return (KO);
	}
	else // no quote
	{
		if(export_no_quote(exported, var, *tmp) == KO)
			return (KO);
	}
	return (OK);
}

int export_check(char **tmp, char *var)
{
	int i;
	
	if (has_equal(var) == KO)
		return (KO);
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (var[++i] == 34 || var[i] == 39)
		if (var[ft_strlen(var) - 1] != var[i])
			return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	if (var[i] == 34 || var[i] == 39)
	{
		*tmp = ft_strdup(var + i + 1);
		if (!*tmp)
			return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
		(*tmp)[ft_strlen(*tmp) - 1] = '\0';
	}
	else
	{
		*tmp = ft_strdup(var + i);
		if (!*tmp)
			return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}
/*
check for format with =
check for no free quote, rm the last quote if there is
dup the string after =
*/

int export_no_quote(char **exported, char *var, char *tmp)
{
	int y;

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

int export_single_quote(char **exported, char *var, char *tmp)
{
	int i;
	int y;
	
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

int	export_double_quote(t_data *minishell, char **exported, char *tmp,
		char *var)
{
	char	**expanded_exported;
	char *dollar;
	int y;

	expanded_exported = NULL;
	*exported = ft_strdup(tmp);
	if (!*exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	expanded_exported = ft_split(*exported, ' ');
	if (!expanded_exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	y = -1;
	while (expanded_exported[++y])
	{
		if (expanded_exported[y][0] == '$') // look just for $
		{
			dollar = ft_strdup(expanded_exported[y]);
			if (!dollar)
				return (free_export_malloc(expanded_exported, tmp, *exported));
			free(expanded_exported[y]);
			expanded_exported[y] = dollar_expansion(dollar, D_QUOTE, minishell);
			free(dollar);
			if (!expanded_exported[y])
				free_export_malloc(expanded_exported, tmp, *exported);
		}
		else if (has_dollar(expanded_exported[y]) == OK)
		{
			int i;
			char *dup;
			i = -1;
		// looking for $ in the string 
			while(expanded_exported[y][++i])
				if(expanded_exported[y][i] == '$')
					break ;
			dup = ft_strdup(expanded_exported[y] + i);
			if (!dup)
				return (free_export_malloc(expanded_exported, tmp, *exported));
			dollar = dollar_expansion(dup, D_QUOTE, minishell);
			free(dup);
			if (!dollar)
				return (free_export_malloc(expanded_exported, tmp, *exported));
			if(dollar[0])
			{
				expanded_exported[y][i] = '\0';
				expanded_exported[y] = strjoin_wfree(expanded_exported[y], dollar);
			}
			free(dollar);
			if (!expanded_exported[y])
				return (free_export_malloc(expanded_exported, tmp, *exported));
		}
	}
	free(*exported);
	*exported = NULL;
	y = -1;
	while (expanded_exported[++y])
	{
		expanded_exported[y] = strjoin_wfree(expanded_exported[y], " ");
		if (!expanded_exported[y])
			return (free_export_malloc(expanded_exported, tmp, *exported));
	}
	return(build_the_export(exported, expanded_exported, var, tmp));
}

int build_the_export(char **exported, char **expanded_exported, char *var, char *tmp)
{
	int i;
	int y;

	y = -1;
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	*exported = ft_calloc(++i + 1, sizeof(char));
	if (!*exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	while (++y < i)
		(*exported)[y] = var[y];
	(*exported)[y] = '\0';
	i = -1;
	while (expanded_exported[++i])
	{
		*exported = strjoin_wfree(*exported, expanded_exported[i]);
		if (!*exported)
			return (free_export_malloc(expanded_exported, tmp, *exported));
	}
	free_double_char(expanded_exported);
	if ((*exported)[ft_strlen(*exported) - 1] == ' ')
		(*exported)[ft_strlen(*exported) - 1] = '\0';
	return (OK);
}

int	free_export_malloc(char **expanded_exported, char *tmp, char *exported)
{
	if (expanded_exported)
		free_double_char(expanded_exported);
	if (tmp)
		free(tmp);
	if (exported)
		free(exported);
	return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
}

int has_dollar(char *var)
{
	int i;

	i = -1;
	while (var[++i])
		if (var[i] == '$')
			return (OK);
	return (KO);
}

int	has_equal(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			return (OK);
	return (KO);
}
