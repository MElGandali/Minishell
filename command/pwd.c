/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/19 18:51:10 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	pwd_command(void)
{
	char *curdir;
	curdir = NULL;
	curdir = getcwd(curdir,sizeof(curdir));
	printf("%s\n", curdir);
	return (0);
}
