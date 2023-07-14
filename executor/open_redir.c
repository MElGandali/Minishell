/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:32:14 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 23:40:15 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_redir_in(t_cmd *cmd, int i)
{
	int	fd;

	if (check_ambiguous(&cmd->red[i + 1]) == 1)
	{
		print_ambiguous_error();
		return (1);
	}
	fd = open(cmd->red[i + 1].data, O_RDONLY, 0644);
	if (fd < 0 || access(cmd->red[i + 1].data, F_OK | W_OK) == -1)
	{
		g_exit = 1;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->red[i + 1].data, 2);
		ft_putstr_fd(": ", 2);
		if (access(cmd->red[i + 1].data, F_OK) == -1)
			ft_putstr_fd("No such file or directory", 2);
		else if (access(cmd->red[i + 1].data, W_OK) == -1)
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	open_dredir_out(t_cmd *cmd, int i)
{
	int	fd;

	if (check_ambiguous(&cmd->red[i + 1]) == 1)
	{
		print_ambiguous_error();
		return (1);
	}
	fd = open(cmd->red[i + 1].data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || access(cmd->red[i + 1].data, F_OK | W_OK) == -1)
	{
		g_exit = 1;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->red[i + 1].data, 2);
		ft_putstr_fd(": ", 2);
		if (access(cmd->red[i + 1].data, F_OK) == -1)
			ft_putstr_fd("No such file or directory", 2);
		else if (access(cmd->red[i + 1].data, W_OK) == -1)
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	open_redir_out(t_cmd *cmd, int i)
{
	int	fd;

	if (check_ambiguous(&cmd->red[i + 1]) == 1)
	{
		print_ambiguous_error();
		return (1);
	}
	fd = open(cmd->red[i + 1].data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0 || access(cmd->red[i + 1].data, F_OK | W_OK) == -1)
	{
		g_exit = 1;
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->red[i + 1].data, 2);
		ft_putstr_fd(": ", 2);
		if (access(cmd->red[i + 1].data, F_OK) == -1)
			ft_putstr_fd("No such file or directory", 2);
		else if (access(cmd->red[i + 1].data, W_OK) == -1)
			ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	open_in_out(t_cmd *cmd, int i, int j)
{
	if (cmd[i].red[j].name == 4)
	{
		if (open_redir_in(&cmd[i], j) == 1)
			return (1);
		g_exit = 0;
	}
	else if (cmd[i].red[j].name == 5)
	{
		if (open_redir_out(&cmd[i], j) == 1)
			return (1);
		g_exit = 0;
	}
	return (0);
}

int	open_redirect(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (j < cmd[i].nb_red)
	{
		if (cmd[i].red[j].name == 4 || cmd[i].red[j].name == 5)
		{
			if (open_in_out(cmd, i, j) == 1)
				return (1);
			j++;
		}
		else if (cmd[i].red[j].name == 7)
		{
			if (open_dredir_out(&cmd[i], j) == 1)
				return (1);
			g_exit = 0;
			j++;
		}
		j++;
	}
	return (0);
}
