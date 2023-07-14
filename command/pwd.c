/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 15:22:48 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_command(void)
{
	char	*curdir;

	curdir = NULL;
	curdir = getcwd(curdir, sizeof(curdir));
	ft_printf("%s\n", curdir);
	g_exit = 0;
}
