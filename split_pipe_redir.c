/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:22 by maddou            #+#    #+#             */
/*   Updated: 2023/05/19 15:05:45 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int check_token(t_lexer *lex, int i)
{
	if (ft_strnstr(lex->word[i], "|") == 0 ||ft_strnstr(lex->word[i], "<<") == 0
		|| ft_strnstr(lex->word[i], ">>") == 0 || ft_strnstr(lex->word[i], "<") == 0
		|| ft_strnstr(lex->word[i], ">") == 0 || ft_strnstr(lex->word[i], ">|") == 0   
		|| ft_strnstr(lex->word[i], "|>") == 0 || ft_strnstr(lex->word[i], "|<") == 0)
			return (0);
	return (1);
}

void count_tokens (t_lexer *lex)
{
	int i;
	int j;

	i = 0;
	lex->word_nb = 0;
	while(lex->word[i])
	{
		if (check_token(lex, i) == 0)
		{
				j = 0;
				while (lex->word[i][j])
				{
					if ((lex->word[i][j] == '\'' || lex->word[i][j] == '\"') || (!(lex->word[i][j] == '>' 
						|| lex->word[i][j] == '<' || lex->word[i][j] == '|')))
					{
						 while(!(lex->word[i][j] == '>' || lex->word[i][j] == '<' 
							|| lex->word[i][j] == '|') && lex->word[i][j] != '\0')
							{
								if (lex->word[i][j] == '\'' || lex->word[i][j] == '\"')
									j = skip_quote(lex->word[i], j);
								j++;
							}
						lex->word_nb++;
					}
					if ((lex->word[i][j] == '>' || lex->word[i][j] == '<' || lex->word[i][j] == '|') 
						&& lex->word[i][j] != '\0')
					{
						while((lex->word[i][j] == '>' || lex->word[i][j] == '<' 
							|| lex->word[i][j] == '|') && lex->word[i][j] != '\0')
							j++;
						lex->word_nb++;
					}
				}
		}
		else
			lex->word_nb++;
		i++;
		}
	}

int    find_word(t_lexer *lex, int i, int j)
{
	if (lex->word[i][j] == '|' || lex->word[i][j] == '>' || lex->word[i][j] == '<')
	{
		while ((lex->word[i][j + 1] == '|' || lex->word[i][j + 1] == '>' 
		|| lex->word[i][j + 1] == '<') && lex->word[i][j + 1]) // if we change the || to && we will find that it split every redirection seperately even if they're next to each other
			j++;
		lex->end = j;
	}
	else if (lex->word[i][j] != '|' || lex->word[i][j] != '>' || lex->word[i][j] != '<')
	{
		while ((lex->word[i][j] != '|' && lex->word[i][j] != '>' 
		&& lex->word[i][j] != '<') && lex->word[i][j + 1]) //"qqdwqdq'" |'|' >> '|qdqwd' "|"         'qw'     //ok|>ok this test will work if we do j + 1 here -> lex->word[i][j + 1]
		{
			if (lex->word[i][j] == '\"' || lex->word[i][j] == '\'')
				j = skip_quote(lex->word[i], j);
			 // "hello| " '|'       "\"|he;lo
			if(lex->word[i][j + 1] == '|' || lex->word[i][j + 1] == '>' || lex->word[i][j + 1] == '<')
					break;
			j++;   
		}
		lex->end = j;
	}//<< qwdqd'qwdq"' q <"qwdq"qd           '      '
	return (j);
}

int split_pipe_redir(t_lexer *lex)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	count_tokens(lex);
	lex->token = (char **)malloc(sizeof(char *) * (lex->word_nb + 1));
	if (!lex->token)
		return (0);
	while (lex->word[i] != NULL)
	{
		j = 0;
		if (ft_strnstr(lex->word[i], ">") == 0
			|| ft_strnstr(lex->word[i], "<") == 0
			|| ft_strnstr(lex->word[i], "|") == 0)
		{
			while(lex->word[i][j] != '\0')
			{
				lex->start = j;
				j = find_word(lex, i, j);
				lex->token[k++] = ft_substr(lex->word[i], lex->start, lex->end - lex->start);
				j++;
			}
		}
		else
			lex->token[k++] = ft_substr(lex->word[i], 0, ft_strlen(lex->word[i]) - 1);
		i++;
	}
	lex->token[k] = NULL;
	
		// printf("%d\n", lex->word_nb);
		// i = 0;
		// while (lex->token[i])
		// {
			
		// 	printf("%s\n", lex->token[i]);
		// 	i++;
		// }
	return (1);
}

