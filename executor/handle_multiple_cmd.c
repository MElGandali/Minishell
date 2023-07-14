/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:34:55 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 23:39:24 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(char *command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return (0);
	while (command[i] != '\0')
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exec_cmd(t_parser *parser, int i)
{
	char	*execpath;

	if (check_path(parser->comm[i].new_cmd[0]) == 0)
		execpath = (char *)find_execpath(parser, i);
	else
		execpath = ft_strdup(parser->comm[i].new_cmd[0]);
	if (is_builtin(parser->comm[i].new_cmd) == 0)
		builtin_commands(parser, i);
	else
	{
		execve((char const *)execpath, parser->comm[i].new_cmd,
			parser->lex->ar_env);
		if (execpath != NULL && execpath[0] == '/')
			print_error(parser, execpath, i);
		print_error(parser, execpath, i);
	}
}

void	exec_cmd_in_pipe_utils(t_parser *parser, int i, int fd_her)
{
	if (parser->comm[i].nb_red > 0)
		check_redirect(&parser->comm[i], fd_her);
	if (parser->comm[i].new_cmd[0] != NULL)
	{
		exec_cmd(parser, i);
		if (is_builtin(parser->comm[i].new_cmd) == 0)
		{
			free_parser(parser);
			exit(0);
		}
	}
	else
	{
		execve(NULL, parser->comm[i].new_cmd, parser->lex->ar_env);
		print_error(parser, NULL, i);
	}
}

void	exec_cmd_in_pipe(t_parser *parser, int *cid, int i, int fd_her)
{
	int	fd[2];
	int	fd_d;

	if (open_redirect(parser->comm, i) == 0)
	{
		fd_her = 0;
		if (i < parser->lex->pipe_nb - 1)
		{
			if (pipe(fd) == -1)
				fd_error(parser);
		}
		fd_her = handle_heredoc(parser, i);
		cid[i] = fork();
		if (cid[i] == 0)
		{
			dup_and_close(parser, fd_d, fd[1], i);
			exec_cmd_in_pipe_utils(parser, i, fd_her);
		}
		if (i > 0)
			close(fd_d);
		fd_d = fd[0];
		close(fd[1]);
	}
}
