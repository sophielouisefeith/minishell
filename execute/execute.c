/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/09/08 14:48:18 by SophieLouis   ########   odam.nl         */
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

static void		invoke_another_program(t_command **command, t_env **_env)
{
    int     ret;
    

    ret = fork();
    if (ret == -1)
            printf("ERROR IN FORK");
    if (ret == 0)
    {
			execve((*command)->array[0], (*command)->array, env_ll_to_array(*_env));
            printf("Je komt nooit hier terug, tenzij execve faalt\n");
            printf("[%s]\n", strerror(errno));
			// 	printf("Je komt nooit hier terug, tenzij execve faalt\n");						
			exit(1);																		//welke exit code?
    }
	if (ret != 0)
        wait(NULL);
}

/*
** Printf's:
		// sleep(1);
		// printf("To kill pid = [%d]\n", ret);
		// kill(ret, SIGTERM);
		// printf("FORKED ID == 0 [%5d]			Child-process\n", ret);
	// printf("Parent Pid = [%d]\n", getpid());
		// printf("Wait: Dit pas printen nadat child is afgerond\n");
		// printf("Child Pid = [%d]\n", getpid());
				// printf("Execute builtin Pid = [%d]\n", getpid());
		// printf("FORKED ID != 0 [%5d]			Parent-process\n", ret);
	// printf("-------THE END------ FORKED ID = [%d]\n", ret);	
					// while (1)
					// {
						// printf("Child Pid = [%d]\n", getpid());
						// sleep(1);
					// }	
*/

void            execute(t_command **command, t_env **_env)
{

        printf("------------KOM JE HIER-----------\n");
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
        if ((*command)->input)
            fdin = open((*command)->input->str_input, O_RDONLY);
        else
            fdin = dup(tmpin);
        i = 0;
        while (i < len_list)
        {
			parameter_expansion(command, *_env);
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
			if ((*command)->builtin == builtin_no)
				invoke_another_program(command, _env);
			else
				execute_builtin(command, _env);
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
}






//waitpid(ret, NULL, 0);                                       //Lijkt niks meer toe te voegen?