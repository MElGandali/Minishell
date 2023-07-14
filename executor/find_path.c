/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:27:03 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 19:17:46 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i + 1])
				i++;
		}
		i++;
	}
	return (count);
}

char	**join_path(t_parser *parser, char **pathname, int i, int *j)
{
	while (pathname[*j])
	{
		pathname[*j] = ft_strjoin(pathname[*j], "/");
		pathname[*j] = ft_strjoin(pathname[*j], parser->comm[i].new_cmd[0]);
		if ((access(pathname[*j], X_OK) == 0))
			break ;
		(*j)++;
	}
	return (pathname);
}

char*const	*find_execpath(t_parser *parser, int i)
{
	char	*pathenv;
	char	**pathname;
	char	*path;
	int		nb;
	int		j;

	nb = 0;
	j = 0;
	path = NULL;
	pathenv = get_env(parser, "PATH");
	if (pathenv == NULL)
		return (NULL);
	pathname = malloc(sizeof(char *) * (path_count(pathenv, ':') + 1));
	if (!pathname)
		return (NULL);
	pathname = ft_split(pathenv, ':', &nb);
	pathname = join_path(parser, pathname, i, &j);
	if (pathname[j] != NULL)
		path = ft_strdup(pathname[j]);
	free_double_array(pathname);
	return ((char *const *)path);
}
