/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:53:39 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 14:38:29 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_command_utils(t_parser *parser, char *envar, char *homedir)
{
	homedir = get_env(parser, envar);
	update_env(parser, "OLDPWD");
	if (homedir == NULL)
	{
		ft_printf("bash: cd: %s not set\n", envar);
		g_exit = 1;
	}
	else
	{
		chdir(homedir);
		update_env(parser, "PWD");
	}
}

void	cd_command(t_parser *parser, char **argv)
{
	char	*homedir;

	homedir = NULL;
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
		cd_command_utils(parser, "OLDPWD", homedir);
	else if (argv[1] == NULL)
		cd_command_utils(parser, "HOME", homedir);
	else
	{
		update_env(parser, "OLDPWD");
		if (chdir(argv[1]) != 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putchar_fd(' ', 2);
			perror(NULL);
			g_exit = 1;
		}
		else
		{
			homedir = ft_substr(argv[1], 0, ft_strlen(argv[1]));
			update_env(parser, "PWD");
		}
	}
}
