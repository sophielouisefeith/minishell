/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_signal.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 10:32:51 by maran         #+#    #+#                 */
/*   Updated: 2020/09/04 11:30:13 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//TEST

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
 #include <sys/wait.h>

/*
** SIGINT (CTRL-C), interrupts the proces and tells it to end (default).
**
** Bash:
	- CTRL-C		Stops child proces, not parent.
*/


// void 		sighandler(int signum)
// {
	
// }

int			main()
{
	// signal(SIGINT, sighandler);

	printf("Parent Pid = [%d]\n", getpid());
	int id = fork();
	if (id == -1)
	{
	 	printf("error in fork");
		return (1);
	}
	if (id == 0)
	{
		printf("FORKED ID == 0 [%5d]			Child-process\n", id);
		// while (1)
		// {
			printf("Child Pid = [%d]\n", getpid());
			sleep(1);
		// }
	}
	else
	{
		wait(NULL);											// Komt niet voorbij dit punt, totdat child proces is afgerond.
		printf("Wait: Dit pas printen nadat child is afgerond\n");
		printf("FORKED ID != 0 [%5d]			Parent-process\n", id);
		// sleep(1);
		// printf("To kill pid = [%d]\n", id);
		// kill(pid, SIGKILL);								// Sends a signal to a proces
	}
	printf("-------THE END------ FORKED ID = [%d]\n", id);
	
	return (0);
}
