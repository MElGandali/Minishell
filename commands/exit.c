/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:16:16 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 15:18:55 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_num_args_error(t_parser *parser, char **argv)
{
	ft_printf("bash: exit: %s: numeric argument required\n", argv[1]);
	g_exit = 255;
	free_parser(parser);
	exit(255);
}

void	exit_cases(t_parser *parser, char **argv, int i)
{
	int	ch;

	ch = 0;
	if (argv[1] == NULL)
	{
		free_parser(parser);
		exit(g_exit);
	}
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i]) != 0)
		{
			ch = 1;
			break ;
		}
		i++;
	}
	if (ch == 1 || (ft_atoi(argv[1]) > LLONG_MAX && argv[1][0] != '-'))
		exit_num_args_error(parser, argv);
	if (argv[2])
	{
		ft_printf("bash: exit: too many arguments\n");
		g_exit = 1;
	}
}

void	exit_command(t_parser *parser, char **argv)
{
	long long int	status;
	int				i;
	int				ch;

	i = 0;
	ch = 0;
	exit_cases(parser, argv, i);
	if (g_exit != 1)
	{
		status = ft_atoi(argv[1]);
		g_exit = status;
		free_parser(parser);
		exit(status);
	}
}
