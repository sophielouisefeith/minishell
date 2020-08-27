/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:30 by sfeith        #+#    #+#                 */
/*   Updated: 2020/08/27 21:43:59 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"

static int		write_echo(t_command *command, t_env *_env, int y)
{
	int		space;
	int 	ret;

	ret = 0;
	space = 0;
	while (command->array[y])
	{
		if (space != 0)
			ret = write(1, " ", 1);
		if (command->array[y][0] == '$' && command->quote[y] != token_quote)			//new
			command->array[y] = parameter_expansion(command, _env, y);
		ret = write(1, command->array[y], ft_strlen(command->array[y]));
		y++;
		space++;		
	}
	return (ret);
}

int				echo(t_command *command, t_env *_env)
{
	int		flag_n;
	int		y;
	int		ret;

	ret = 0;
	flag_n = 0;
	y = 0;
	if (!ft_strcmp(command->array[0], "-n"))
	{
		flag_n = 1;
		y++;
	}
	ret = write_echo(command, _env, y);
	if (!flag_n)
		ret = write(1, "\n", 1);
	return (ret);
}
