/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_maran.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 10:06:46 by maran         #+#    #+#                 */
/*   Updated: 2020/08/20 13:27:08 by maran         ########   odam.nl         */
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
        
        // if ((*command)->input->str_input)
        //     fdin = open((*command)->input->str_input, O_RDONLY);
        // else
            fdin = dup(tmpin);

        // printf("In execute_maran\n");
        i = 0;
        while (i < len_list)
        {
            // printf("In execute_maran 2\n");
            // dup2(fdin, 0);
            // close(fdin);
            
            // if (i == len_list)
            // {
            //     if ((*command)->output->str_output)
            //         fdout=open((*command)->output->str_output, O_RDONLY);
            //     else
            //         fdout = dup(tmpout);
            // }
            // else
            // {
            //     pipe(fdpipe);
            //     fdout = fdpipe[1];
            //     fdin  = fdpipe[0];
            // }
            // printf("In execute_maran3\n");
            // dup2(fdout,1);
            // close(fdout);
            
            // printf("In execute_maran4\n");
            ret = fork();
            if (ret == -1)
                printf("ERROR IN FORK");
            // printf("In execute_maran5\n");
            if (ret == 0)                //child
            {
                // execvp(scmd[i].args[0], scmd[i].args);          //uitzoeken!
                // printf("In child\n");
                execute_builtin(command);
                printf("Komt nooit hier toch?\n");
                //  if (execve("./sub", (*command)->array, env) == -1)
                //     perror("Execve failed!\n");
                // exit(1);
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
