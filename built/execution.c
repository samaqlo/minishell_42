/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/10 15:48:38 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    ft_execution(t_cmd_lines *lines)
// {
//    pid_t pid = fork();
//    (void)lines;
//     int fd[2];
//     if(pipe(fd) < 0)
//     {
//         perror("pipe");
//         exit(1);
//     }
//     if (pid == -1) {
//         perror("fork");
//         exit(1);
//     }
//     else if (pid == 0)
//     {
//         dup2(fd[1], 1);
//         close(fd[0]);
//         if (execve("/bin/ls", "/bin/ls -la", environ) == -1) {
//              perror("execve");
//              exit(1);
//         }
//         close(fd[1]);
//     }
//     else 
//     {
//         int status;
//         waitpid(pid, &status, 0);
//         dup2(fd[0], 0);
//         close(fd[0]);
//         close(fd[1]);
//     }

//     return ;
// }

     