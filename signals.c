/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:34:10 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 09:28:41 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COLOR_PROMPT	"\033[1;34mminishell-$ \033[0m"

/*
** End of File	--> CTRL D:
*/
void			ctrl_d(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

/*
** When invoking another program with execve the original sighandler has to be reset:
** Don't print a prompt en no backspaces anymore
*/

void			signal_reset(int sig_num) 
{
	(void)sig_num;
	return ;
	
}

void			sighandler_execve(int status)
{
	if (status == SIGINT)
		write(1, "\n", 1);
	if (status == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	g_exit_status = status + 128;
}

/*
** SIGINT	- interrupt signal	--> CTRL C
** SIGQUIT	- quit signal		--> CTRL backslash 
** The Original sighandler:
*/

void			sighandler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\b\b  \n", 5);
		write(1, COLOR_PROMPT, 23);
	}
	if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}
