/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/23 22:03:22 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	pwd_command(void)
{
	char *curdir;
	curdir = NULL;
	curdir = getcwd(curdir,sizeof(curdir));
	printf("%s\n", curdir);
}
