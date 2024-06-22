/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:42:40 by phwang            #+#    #+#             */
/*   Updated: 2023/12/02 00:07:22 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *str, ...);
void			var_print(va_list list_arg, const char **str, int *len);

void			ft_putnbr_len(int n, int *len);
void			ft_putnbr_base(unsigned int n, char *base, int *len);
void			ft_putnbr_ptr(unsigned long n, char *base, int *len);
void			ft_putptr(unsigned long n, char *base, int *len);

void			ft_putchar_len(char c, int *len);
void			ft_putstr_len(char *s, int *len);
unsigned int	ft_lilstrlen(char *str);

#endif