/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:48:34 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:34:37 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define FLAG_FREE_BUFFER 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct l_list_str
{
	char				*content;
	struct l_list_str	*next;
}						t_str;

char					*get_next_line(int fd, int flag);
int						first_step(int fd, t_str **head, char **stock);
int						stock_analyse(char *stock);
int						ft_read(int fd, t_str **head, char **stock);
int						n_stock(t_str **head, char **stock, int fd);
int						separate_stock(t_str **head, char **stock);
int						build_line(t_str *head, char **line, char *stock);

t_str					*ft_lstnew(char **stock);
void					ft_lstclear(t_str **head);
void					ft_lstadd_back(t_str **head, t_str *elem);
int						ft_len(t_str *head, char *stock, int choice);

#endif
