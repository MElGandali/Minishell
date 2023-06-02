/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:11:27 by maddou            #+#    #+#             */
/*   Updated: 2023/06/02 18:25:14 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

// int valide_identification(char c)
// {
//     if (!(ft_isalpha(c) && c !='_'))
//         return (1);
//     return (0);
// }

void add_new_export(t_lexer *lex, char **exp)
{
    if (!(ft_isalpha(exp[1][0]) && exp[1][0] != '_'))
    {
        
    }
    else    
        printf ("bash: export:  `%s': not a valid identifier\n",exp[1]);
}