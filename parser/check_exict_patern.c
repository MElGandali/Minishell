/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exict_patern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:13:36 by maddou            #+#    #+#             */
/*   Updated: 2023/07/15 00:06:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialization(t_init *init, t_cmd *cmd)
{
	init->check = 0;
	init->openfile = opendir(".");
	init->i = 0;
	init->x = cmd->dt_nb - 1;
}

t_data	*fill_wildcard_data(t_cmd *cmd, int j, int *nb_w)
{
	struct dirent	*entry;
	t_init			init;

	initialization(&init, cmd);
	while (1)
	{
		entry = readdir(init.openfile);
		if (!entry)
			break ;
		if (nb_w[init.i] == 1)
		{
			if (init.check++ == 0)
				initialization_data_cmd(entry->d_name, cmd, j);
			else
				initialization_data_cmd(entry->d_name, cmd, init.x);
			init.x++;
		}
		init.i++;
	}
	closedir(init.openfile);
	return (cmd->dt);
}

char	*copy_data(char *data)
{
	char	*co_data;
	int		j;

	j = 0;
	co_data = ft_strdup(data);
	while (co_data[j] != '\0')
	{
		if (co_data[j] == '\'' || co_data[j] == '\"')
			j = skip_quote(co_data, j);
		else if (co_data[j] == '*')
			co_data[j] = '\n';
		j++;
	}
	return (co_data);
}

char	**handal_quote(char **patern)
{
	char	*new_pa;
	int		i;
	int		j;

	i = 0;
	while (patern[i] != NULL)
	{
		new_pa = NULL;
		j = 0;
		while (patern[i][j] != '\0')
		{
			if (patern[i][j] == '\'' || patern[i][j] == '\"')
				new_pa = if_quote_fill(patern[i], &j, new_pa);
			else
				new_pa = ft_copier(patern[i][j], new_pa);
			j++;
		}
		free(patern[i]);
		patern[i] = ft_strdup(new_pa);
		free(new_pa);
		i++;
	}
	return (patern);
}

int	*check_exict_patern(t_parser *parser, char *data, int *nb_w, DIR *openfile)
{
	int		i;
	int		j;
	int		nb_arg;
	char	**patern;
	char	*co_data;

	nb_arg = 0;
	i = 0;
	j = 0;
	ft_calcule_etoile(data, &i);
	co_data = copy_data(data);
	patern = ft_split(co_data, '\n', &nb_arg);
	free(co_data);
	patern = handal_quote(patern);
	if (i == 1)
	{
		if (nb_arg == 1)
			nb_w = find_number_w_one_arg(data, nb_w, patern);
		else
			nb_w = find_number_w_mult_arg(parser, nb_w, patern, nb_arg);
	}
	else
		nb_w = find_mult_etoile(nb_w, data, patern, openfile);
	free_double_array(patern);
	return (nb_w);
}
