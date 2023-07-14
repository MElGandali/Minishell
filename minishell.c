/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:33:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/07/13 20:05:36 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit = 0;

void	all_work(t_lexer *lex)
{
	if (tokenizer(lex) == -1)
		return ;
	if (parser(lex) == -1)
		return ;
}

// void	reprompt(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_exit = 1;
// 		ft_printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_lexer	lex;

	(void)ac;
	(void)av;
	lex.env = NULL;
	lex.exp = NULL;
	// signal(SIGINT, reprompt);
	// signal(SIGQUIT, SIG_IGN);
	creating_new_env(&lex, env);
	while (1)
	{
		lex.line = readline("bash$ ");
		// if (lex.line == NULL)
		// 	ft_printf("exit\n");
		if (!lex.line)
			exit(g_exit);
		if (lex.line[0] != '\0')
			add_history(lex.line);
		all_work(&lex);
	}
	return (0);
}
