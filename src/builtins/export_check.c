/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:31:45 by phwang            #+#    #+#             */
/*   Updated: 2024/08/25 15:46:24 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_check(char **tmp, char *var)
{
	int	i;

	if (has_equal(var) == KO)
		return (KO);
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	// look for " or ' in the string
	// if (var[++i] == 34 || var[i] == 39)
	// 	if (var[ft_strlen(var) - 1] != var[i])
	// 		return (ft_putstr_fd(EXPORT_ERR, STDERR_FILENO), KO);
	// if (var[i] == 34 || var[i] == 39)
	// {
	// 	*tmp = ft_strdup(var + i + 1);
	// 	if (!*tmp)
	// 		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	// 	(*tmp)[ft_strlen(*tmp) - 1] = '\0';
	// }
	// else
	// {
		*tmp = ft_strdup(var + i);
		if (!*tmp)
			return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	// }
	return (OK);
}
/*
check for format with =
check for no free quote, rm the last quote if there is
dup the string after =
*/

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

int	has_dollar(char *var)
{
	int	i;

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

int has_multiple_dollar(char *var)
{
	int	i;
	int	dollar;

	i = -1;
	dollar = 0;
	while (var[++i])
		if (var[i] == '$')
			dollar++;
	if (dollar > 1)
		return (OK);
	return (KO);
}
