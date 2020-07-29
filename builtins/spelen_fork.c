/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spelen_fork.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 12:05:08 by maran         #+#    #+#                 */
/*   Updated: 2020/07/27 12:57:57 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

// read from fd 0
// write to fd 1

int             main(int argc, char **argv)
{
    int fd[2];
    int id;

    if (pipe(fd) == -1)                                 //pipe reads and writes to fd
    {
        printf("ERROR in opening the pipe\n");
        return (1);
    }
    id = fork();                                        //fd worden nu overgerfd naar child 
    if (id == -1)
        printf("ERROR with fork\n");
    if (id == 0)                                        // return value van fork == 0, dan ben je in het child proces
    {                                                   //In dit child proces write ik alleen maar, omdat ik niet lees kan ik deze fd al sluiten
        close(fd[0]);
        int x;
        printf("In child proces: > input a number: \n");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));                  //schrijf naar fd 1
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));                   //lees van fd[0] en sla op in y
        close(fd[0]);
        printf("In parent proces: > via pipe van child proces ontvangen [%d]\n", y);
    }
    // if (id != 0)                                        //Stop de uitvoer van de parent proces tot het child proces is afgerond
    //     wait();
    return (0);
}