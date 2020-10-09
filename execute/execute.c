/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/09 16:57:22 by SophieLouis   ########   odam.nl         */
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
		printf("-------------invoke another program?\n");
		execve((*command)->array[0], (*command)->array, env_ll_to_array(*_env));
		printf("[%s]\n", strerror(errno));					
		exit(1);																		//welke exit code?
    }
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
        	g_exit_status = WEXITSTATUS(status);
	}
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
			
			//printf("Value **Commmand = [%p] > naar adres > *command= [%p] (= HEAD NODE)\n", command, *command);
			check_specials(command, *_env);
			//parameter_expansion(command, *_env);
			
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
			// printf("IN EXECUTE\n");
			if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
				invoke_another_program(command, _env);
			if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
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