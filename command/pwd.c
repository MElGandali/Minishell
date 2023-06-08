/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:48:38 by mel-gand          #+#    #+#             */
/*   Updated: 2023/06/08 01:13:59 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	pwd_command(char **argv)
{
	char *curdir;
	curdir = getcwd(curdir,sizeof(curdir));
	printf("%s\n", curdir);
}
int main (int argc, char **argv)
{
	(void)argc;
	pwd_command(argv);

}
