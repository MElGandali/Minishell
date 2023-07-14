/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:47:44 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/14 17:21:05 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_parser *parser, char *execpath, int i)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(parser->comm[i].new_cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	free(execpath);
	free_parser(parser);
	exit(127);
}

void	fd_error(t_parser *parser)
{
	perror("pipe");
	free_parser(parser);
	exit(2);
}

void	waitchild_and_save_exit(int *cid, int i)
{
	int	e_code;

	e_code = 0;
	waitpid(cid[i], &e_code, 0);
	if (WIFSIGNALED(e_code))
		g_exit = WTERMSIG(e_code) + 128;
	else if (WIFEXITED(e_code))
		g_exit = WEXITSTATUS(e_code);
}

void	dup_and_close(t_parser *parser, int fd_in, int fd_out, int i)
{
	if (i != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (i != parser->lex->pipe_nb - 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}

void	handle_cmd(t_parser *parser)
{
	int	i;
	int	*cid;
	int	fd_her;

	i = 0;
	cid = malloc(sizeof(int) * parser->lex->pipe_nb);
	if (parser->lex->pipe_nb > 1)
	{
		while (i < parser->lex->pipe_nb)
		{
			exec_cmd_in_pipe(parser, cid, i, fd_her);
			i++;
		}
		i = 0;
		while (i < parser->lex->pipe_nb)
		{
			waitchild_and_save_exit(cid, i);
			i++;
		}
	}
	else
		exec_one_cmd(parser, cid, i, fd_her);
	free(cid);
}
