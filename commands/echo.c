/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 19:59:20 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 14:55:48 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detect_flag(char *argv)
{
	int	j;
	int	check;

	j = 0;
	check = 0;
	if (argv[j] == '-' && argv[j + 1] == 'n')
	{
		j++;
		while (argv[j])
		{
			if (argv[j] != 'n')
			{
				check = 0;
				return (0);
			}
			else if (argv[j] == 'n')
				check = 1;
			j++;
		}
		if (check == 1)
			return (1);
	}
	return (check);
}

void	echo_special_var(char **argv, char *newarg)
{
	newarg = special_var(argv);
	ft_printf("%s", newarg);
	free(newarg);
}

void	echo_command(char **argv)
{
	int		i;
	char	*newarg;

	i = 1;
	newarg = NULL;
	if (argv[1] == NULL)
		ft_printf("\n");
	else
	{
		while (argv[i] && detect_flag(argv[i]) == 1)
			i++;
		while (argv[i])
		{
			if (ft_strnstr(argv[i], "$?") == 0 && argv[i])
				echo_special_var(argv, newarg);
			else if (ft_strcmp(argv[i], "$?") != 0)
				ft_printf("%s", argv[i]);
			if (argv[i + 1])
				ft_printf(" ");
			i++;
		}
		g_exit = 0;
		if (detect_flag(argv[1]) == 0)
			ft_printf("\n");
	}
}
