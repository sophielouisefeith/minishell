/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/20 11:24:12 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 16:54:31 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				lstsize(t_command *command)
{
	int		c;

	c = 0;
	while (command)
	{
		command = command->next_command;
		c++;
	}
	return (c);
}

int				fill_fdout(t_output *output, int tmpout)
{
	int		fdout;

	if(output)
	{
		while(output)
		{
			if (output && output->token == token_redirection_greater)
				fdout = open(output->str_output,  O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (output && output->token ==  token_redirection_dgreater)
				fdout = open(output->str_output, O_RDWR | O_CREAT | O_APPEND, 0644);
			output = output->next_output;
		}
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

void			execute_output(t_command **command, t_execute **exe,
								t_env **_env)
{
	(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	dup2((*exe)->fdout,1);
	close((*exe)->fdout);
	builtin_another_program(command, _env);
}

void			initialise_execute(t_command *command, t_execute **exe)
{
	(*exe)->len_list = lstsize(command);
	(*exe)->tmpin = dup(0);
	(*exe)->tmpout = dup(1);
	(*exe)->fdin = dup((*exe)->tmpin);
	(*exe)->i = 0;
}

void			close_execute(t_execute **exe)
{
	//printf("----------closeexecute\n");
	dup2((*exe)->tmpin, 0);
	dup2((*exe)->tmpout, 1);
	close((*exe)->tmpin);
	close((*exe)->tmpout);
}
