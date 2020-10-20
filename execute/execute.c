/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/15 10:33:33 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

static int		lstsize(t_command *command)
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

static int      fill_fdout(t_output *output, int tmpout)
{
    int     fdout;

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

/*
** Waitpid: It suspends execution of the calling process until a child specified by pid argument has changed state.
** WIFEXITED(status): returns true if the child terminated normally.
** WEXITSTATUS(status): returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.
*/

static void		invoke_another_program(t_command **command, t_env **_env)
{
    int     pid;	
	int 	status;

	pid = fork();
    if (pid == -1)
           printf("[%s]", strerror(errno));
    if (pid == 0)
    {
		//printf("-------------invoke another program?\n");
		execve((*command)->array[0], (*command)->array, env_ll_to_array(*_env));
		errno_error((*command)->array[0]);					
		exit(g_exit_status);																		//welke exit code?
    }
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
        	g_exit_status = WEXITSTATUS(status);
	}
}

void			builtin_another_program(t_command **command, t_env **_env)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, _env);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
		execute_builtin(command, _env);
	if ((*command)->builtin == builtin_no_com)		//Twijfel of dit goed gaat. Toegevoegd vanwege $echo hallo
		error_command((*command)->array[0]);
}

/*
** Changelog:
	- Big changes 8/10:
	Om de test cases van boris op te lossen. Mochten er issues zijn de laatste git versie van voor verandering is "solved ctrl d"
** TO DO:
	- korter maken, let op fragiel!
*/


void            *execute(t_command **command, t_env **_env)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
		int     i;
        int     len_list;
        int     fdpipe[2];

        len_list = lstsize(*command);
        tmpin = dup(0);
        tmpout = dup(1);
        i = 0;
        fdin = dup(tmpin);
        while (i < len_list)
        {
			if ((*command)->input)
			{
            	fdin = open((*command)->input->str_input, O_RDONLY);
				if (fdin == -1)
					return (errno = ENOENT, errno_error((*command)->input->str_input));
			}
			check_specials(command, *_env);
			if ((*command)->builtin == builtin_no_com && (!(*command)->array || !(*command)->array[0])) //$echo //lijkt of de 2d huls niet wordt gedelete, naar kijken
				return (0);
            dup2(fdin, 0);
            close(fdin);
            if (i == len_list - 1)
				fdout = fill_fdout((*command)->output, tmpout);
			else if ((*command)->sem && (*command)->output)
			{
					fdout = fill_fdout((*command)->output, tmpout);
					dup2(fdout,1);
					close(fdout);
					builtin_another_program(command, _env);
					fdout = dup(tmpout);
			}
            else if ((*command)->pipe_after)
            {
				if ((*command)->pipe_after && (*command)->output)
				{
					fdout = fill_fdout((*command)->output, tmpout);
					dup2(fdout,1);
					close(fdout);
					builtin_another_program(command, _env);
				}
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }
            else                                                        // ; 
                fdout = dup(tmpout);
			dup2(fdout,1);
            close(fdout);
			if (!(((*command)->sem || (*command)->pipe_after) && (*command)->output))
				builtin_another_program(command, _env);
			if ((*command)->sem)			//gaat dit nog goed?
				fdin = dup(tmpin);
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
		return (0);
}
