/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:55:34 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/25 22:56:28 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ft_printf_H
# define ft_printf_H

// LIBRARIES

# include <stdarg.h>
# include <unistd.h>

//PROTOTYPES

int	ft_printf(const char *str, ...);
int	ft_printchar(char c);
int	ft_printnbr(long nb);
int	ft_printstr(char *str);
int	ft_printuint(unsigned int nb);
int	ft_printhex(unsigned int nb, char c);
int	ft_printpi(unsigned long nb);

#endif