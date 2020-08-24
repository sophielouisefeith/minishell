/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_maran.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 10:06:46 by maran         #+#    #+#                 */
/*   Updated: 2020/08/24 12:20:49 by maran         ########   odam.nl         */
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

static int      fill_fdout(t_output *output, int tmpout)
{
    int     fdout;
    
    if (output)
    {
        while (output)
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
** Next time:   echo hallo maran >file1 >file2 >file3   
                echo pizza is lekker > file4 >>file2

*/

void            execute_maran(t_command **command)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
        int     ret;
        int     i;
        int     len_list;
        int     fdpipe[2];

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
                fdout = fill_fdout((*command)->output, tmpout);
            else if ((*command)->pipe_after)                            //new
            {
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }
            else                                                        //new (overbodig wel mooier)
                fdout = dup(tmpout);
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
            if (ret != 0)                                               //new
                wait(NULL);
;            *command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
        // waitpid(ret, NULL, 0);                                       //Lijkt niks meer toe te voegen?
}
