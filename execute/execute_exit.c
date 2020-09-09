/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 13:54:44 by maran         #+#    #+#                 */
/*   Updated: 2020/09/09 19:06:30 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** Subject: exit without any options 

** Each shell command returns an exit code when it terminates, either
** successfully or unsuccessfully.
** zero = succeffully
** non-zero = error					--> number depends of function
**
** Exit the shell, returning a status of n to the shell’s parent. If n is omitted,
** the exit status is that of the last command executed. 
** Any trap on EXIT is executed before the shell terminates.			----> LET OP BIJ SIGNALS.
** 		exit(n) --> n is restricted to eight bits, so the maximum value is 255.
** 
** echo $? --> exit status of last executed command
**
** Mijn functie:
** exit_status = default 0, otherwise a set exit_status.
** Als geen argumenten dan status laatste command.
** Als wel argumenten dan overruled hij de exit_status:
	- 1. Check of nummeriek
	- 2. Check aantal argumenten, meer dan 1 exit_status op 1. Hij exit niet!
	- 3. Als maar 1 argument en deze is nummeriek, dan exit met deze exitstatus.

** LET OP: volgorde van exit functie belangrijk.
*/

int        execute_exit(t_command *command)
{
	int		argument_0;
	int 	i;
	int		ret;

	i = 0;
	if (!command->array)
	{
		write(1, "exit\n", 6);
		exit(g_exit_status);
	}
	if (command->array[0])
	{
		while (command->array[0][i])
		{
			ret = ft_isdigit(command->array[0][i]);
			if (ret == 0)
			{
				write(1, "exit\nbash: exit: numeric argument required\n", 44);		//Moet nog errormessage waarbij argument door wordt gegeven
				exit(255);
			}
			i++;
		}
	}
	if (command->array[1])
	{
		write(1, "exit\nbash: exit: too many arguments\n", 37);
		return (g_exit_status = 1);
	}
	else
	{
		g_exit_status = ft_atoi(command->array[0]);
		write(1, "exit\n", 6);
		exit(g_exit_status);
	}
}
