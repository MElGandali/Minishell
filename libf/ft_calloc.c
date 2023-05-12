/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:03:52 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/04 16:10:39 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbrs_element, size_t taille_element)
{
	void	*p;
	size_t	s;

	s = nbrs_element * taille_element;
	p = malloc(s);
	if (p != 0)
		ft_bzero(p, s);
	return (p);
}
