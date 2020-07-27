/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spelen_execve.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:51:50 by maran         #+#    #+#                 */
/*   Updated: 2020/07/23 17:36:33 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

/*
** gcc spelen_sub.c -o sub && gcc spelen_execve.c && ./a.out hallo maran
*/

int main(int argc, char **argv, char **envp) 
{
    int i;
    
    i = 0;
    printf("Main program started\n\n");
    printf("Main Pid = %d\n", getpid());
    if (execve("./sub", argv, envp) == -1)
        perror("Execve failed!\n");
    printf("Je komt nooit hier terug, tenzij execve faalt\n");

  return 1;
}