/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:33:42 by mel-gand          #+#    #+#             */
/*   Updated: 2023/05/09 16:09:30 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include"libft.h"

void handler(int signum)
{
    //char *str = NULL;
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        //rl_replace_line("",0);
        rl_redisplay();
    }       
}
int main()
{
    
    //int i = 1;
    
    signal(SIGINT,handler);
    while (1){
    char *str = readline("bash$ "); 
    tokenizer(str);
    // char **split = ft_split(str, ' ');
    // char *path = ft_strjoin("/bin/", split[0]);
    add_history(str);
    if (strcmp(str, "history -c") == 0)
        clear_history();
    // pid_t pid = fork();
    // if (pid == 0)
    // {
    //     if (execve(path, split, NULL) == -1)
    //     {
    //         perror("execve");
    //         exit(EXIT_FAILURE);
    //     }
    // }
    // wait(&i); 
   
}
   
    return (0);  
}
