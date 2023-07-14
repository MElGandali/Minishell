/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:06:48 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/12 17:07:47 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_printchar(char c);
int	ft_printnbr(long nb);
int	ft_printstr(char *str);
int	ft_printuint(unsigned int nb);
int	ft_printhex(unsigned int nb, char c);
int	ft_printpi(unsigned long nb);

#endif