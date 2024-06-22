/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:48:40 by phwang            #+#    #+#             */
/*   Updated: 2024/06/12 19:18:54 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

int	ft_read(int fd, t_str **head, char **stock)
{
	int	size_read;

	size_read = 0;
	if (*stock)
		free(*stock);
	*stock = malloc((BUFFER_SIZE + 1) * sizeof(char *));
	if (!(*stock))
		return (FALSE);
	size_read = (int)read(fd, (*stock), BUFFER_SIZE);
	if ((*head == NULL && size_read == 0) || size_read == -1)
	{
		free(*stock);
		*stock = 0;
		return (TRUE);
	}
	(*stock)[size_read] = '\0';
	if (n_stock(head, stock, fd) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	n_stock(t_str **head, char **stock, int fd)
{
	if (stock_analyse((*stock)) == 1)
	{
		if (separate_stock(head, stock) == FALSE)
			return (FALSE);
	}
	else if (stock_analyse((*stock)) == 2)
	{
		ft_lstadd_back(head, ft_lstnew(stock));
		if (ft_read(fd, head, stock) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	separate_stock(t_str **head, char **stock)
{
	int		pos;
	int		i;
	char	*beg_stock;

	pos = 0;
	while ((*stock)[pos] != '\n')
		pos++;
	beg_stock = malloc((pos + 2) * sizeof(char));
	if (!beg_stock)
		return (FALSE);
	i = -1;
	while (++i <= pos)
		beg_stock[i] = (*stock)[i];
	beg_stock[i] = '\0';
	ft_lstadd_back(&(*head), ft_lstnew(&beg_stock));
	i = -1;
	while ((*stock)[pos + 1 + (++i)])
		(*stock)[i] = (*stock)[pos + 1 + i];
	(*stock)[i] = '\0';
	return (TRUE);
}

int	build_line(t_str *head, char **line, char *stock)
{
	int	len;
	int	i;

	*line = malloc((ft_len(head, stock, 0) + 1) * sizeof(char *));
	if (!(*line))
		return (FALSE);
	len = -1;
	if (head == NULL)
	{
		free(line);
		return (FALSE);
	}
	while (head != NULL)
	{
		i = -1;
		while ((head->content)[++i])
			(*line)[++len] = (head->content)[i];
		head = head->next;
	}
	(*line)[++len] = '\0';
	return (TRUE);
}

char	*get_next_line(int fd, int flag)
{
	char		*line;
	t_str		*head;
	static char	*stock = NULL;

	line = NULL;
	head = NULL;
	if (flag == 1)
	{
		if (stock)
			free(stock);
		stock = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &stock, 0) < 0)
		return (NULL);
	if (first_step(fd, &head, &stock) == FALSE)
		return (NULL);
	if (head == NULL || stock == NULL)
		return (NULL);
	if (build_line(head, &line, stock) == FALSE)
		return (NULL);
	ft_lstclear(&head);
	return (line);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int	fd;

// 	fd = open("map.ber", O_RDONLY);
// 	char *temp = get_next_line(fd);
// 	do {
// 		__builtin_printf("[%s]", temp);
// 		if (temp != NULL)
// 			free(temp);
// 		temp = get_next_line(fd);
// 	} while (temp);
// 	__builtin_printf("[%s]", temp);
// 	close(fd);
// 	return (0);
// }
