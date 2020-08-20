/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_maran.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 10:06:46 by maran         #+#    #+#                 */
/*   Updated: 2020/08/20 18:17:22 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

static int  lstsize(t_command *command)
{
	int c;

	c = 0;
	while (command)
	{
		command = command->next_command;
		c++;
	}
	return (c);
}

static int      fill_fdout(t_command *command, int tmpout)
{
    int     fdout;
    
    if (command->output && command->output->token == token_redirection_greater)
        fdout = open(command->output->str_output,  O_RDWR | O_CREAT | O_TRUNC);
    else if (command->output && command->output->token ==  token_redirection_dgreater)
        fdout = open(command->output->str_output, O_RDWR | O_CREAT | O_APPEND);
    else
        fdout = dup(tmpout);
    return (fdout);
}

/*
** Changelog:
    - Gewijzigd:  
    if ((*command)->pipe_after)    --> ipv else
** TO DO:
    - Na wijziging, lijkt al te werken maar wat zit er dan in fdout? Beter uitzoeken.
*/

void            execute_maran(t_command **command)
{
        int            tmpin;
        int            tmpout;
        int            fdin;
        int             ret;
        int             fdout;
        int             i;
        int             len_list;
        int             fdpipe[2];

        len_list = lstsize(*command);
        tmpin = dup(0);
        tmpout = dup(1);
        if ((*command)->input)
            fdin = open((*command)->input->str_input, O_RDONLY);
        else
            fdin = dup(tmpin);
        i = 0;
        while (i < len_list)
        {
            dup2(fdin, 0);
            close(fdin);
            if (i == len_list - 1)
                fdout = fill_fdout(*command, tmpout);
            if ((*command)->pipe_after)
            {
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }
            dup2(fdout,1);
            close(fdout);
            ret = fork();
            if (ret == -1)
                printf("ERROR IN FORK");
            if (ret == 0)
            {
                execute_builtin(command);
                printf("Komt nooit hier toch?\n");
            }
            *command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
        waitpid(ret, NULL, 0);
}
