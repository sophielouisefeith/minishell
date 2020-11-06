/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 13:54:44 by maran         #+#    #+#                 */
/*   Updated: 2020/11/06 18:12:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		error_exit(t_command *command, int i)
{
	char	*str_built;

	str_built = translate_builtin((command->builtin), NULL);
	write(1, "exit\n", 5);
	write(1, "bash: ", 6);
	write(1, str_built, ft_strlen(str_built));
	write(1, command->array[0], ft_strlen(command->array[0]));
	if (i == 0)
	{
		write(1, ": numeric argument required\n", 28);
		exit(255);
	}
}

static void		exit_part1(t_command *command)
{
	int			i;
	int			ret;

	i = 0;
	while (command->array[0][i])
	{
		ret = ft_isdigit(command->array[0][i]);
		if (ret == 0)
			error_exit(command, ret);
		i++;
	}
}

int				execute_exit(t_command *command)
{
	if (!command->array)
	{
		write(1, "exit\n", 6);
		exit(g_exit_status);
	}
	if (command->array[0])
		exit_part1(command);
	if (command->array[1])
	{
		write(1, "exit\nbash: exit: too many arguments\n", 37);
		g_exit_status = 1;
		return (g_exit_status);
	}
	else
	{
		g_exit_status = ft_atoi(command->array[0]);
		write(1, "exit\n", 6);
		exit(g_exit_status);
	}
}
