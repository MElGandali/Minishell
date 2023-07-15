/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:23:32 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/15 17:36:39 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

int	is_builtin(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[0] != NULL && (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0],
				"cd") == 0 || ft_strcmp(cmd[0], "exit") == 0
			|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "$?") == 0
			|| ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "env") == 0
			|| ft_strcmp(cmd[0], "unset") == 0))
		return (0);
	return (1);
}

void	exec_cmd_builtin(t_parser *parser, int i, int fd_her)
{
	int	std_in;
	int	std_out;

	std_out = 0;
	std_in = 0;
	fd_her = handle_heredoc(parser, i);
	if (open_redirect(parser->comm, i) == 0)
	{
		if (parser->comm[0].nb_red > 0)
			check_redirect(&parser->comm[0], fd_her);
		builtin_commands(parser, i);
		std_out = open("/dev/tty", O_WRONLY);
		std_in = open("/dev/tty", O_RDONLY);
		dup2(std_out, 1);
		dup2(std_in, 0);
		close(std_out);
		close(std_in);
	}
}

void	exec_cmd_not_builtin(t_parser *parser, int *cid, int i, int fd_her)
{
	fd_her = handle_heredoc(parser, i);
	if (open_redirect(parser->comm, i) == 0)
	{
		cid[0] = fork();
		if (cid[0] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (parser->comm[0].nb_red > 0)
				check_redirect(&parser->comm[0], fd_her);
			if (parser->comm[0].new_cmd != NULL)
				exec_cmd(parser, 0);
			else
			{
				free_parser(parser);
				exit(0);
			}
		}
		waitchild_and_save_exit(cid, 0);
	}
}

void	exec_one_cmd(t_parser *parser, int *cid, int i, int fd_her)
{
	if (parser->comm[0].new_cmd != NULL
		&& is_builtin(parser->comm[i].new_cmd) == 0)
		exec_cmd_builtin(parser, i, fd_her);
	else
		exec_cmd_not_builtin(parser, cid, i, fd_her);
}
