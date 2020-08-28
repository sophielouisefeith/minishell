/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 13:54:44 by maran         #+#    #+#                 */
/*   Updated: 2020/08/27 14:02:35 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
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
** Als geen argumenten dan status laatste command, anders 0.
** Als wel argumenten dan overruled hij de exit_status
** Max 1 argumenten, meer dan exit_status op 1. Hij exit niet!
*/

int        execute_exit(t_command *command)
{
	int		argument_0;

	if (!command->array)
		exit(command->exit_status);
	else if (command->array[1])
	{
		printf("exit\nbash: exit: too many arguments\n");
		return (command->exit_status = 1);
	}
	else
	{
		argument_0 = ft_atoi(command->array[0]);
		if (ft_isalnum(argument_0))
		{
			printf("exit\nbash: exit: numeric argument required\n");
			command->exit_status = 255;
		}
		else
			command->exit_status = argument_0;
		exit(command->exit_status);	
	}
}
