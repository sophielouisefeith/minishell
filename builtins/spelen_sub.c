/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spelen_sub.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:53:42 by maran         #+#    #+#                 */
/*   Updated: 2020/07/23 17:38:36 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int         main(int argc, char **argv, char **envp)
{
    int i;
    
    i = 1;
    printf("----------------------------\n");
    printf("Je zit in het subprogramma\n");
    printf("Sub Pid = %d    -->Zelfde als main want PID is overgenomen door sub \n", getpid()); 
    printf("file name = [%s]\n", argv[0]);
    while (argv[i])
    {
        printf("argv[%d] = [%s]\n", i, argv[i]);
        i++;
    }
    i = 0;
    printf("\n--------------ENV-----------\n");
    while (i < 5)
    {
        printf("%s\n", envp[i]);
        i++;
    }
    printf("----------------------------\n\n");
    printf("Einde subprogramma\n");
    printf("----------------------------\n");
    return (0);    
}
