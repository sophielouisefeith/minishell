/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_kapot.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/30 15:26:30 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

	if (output)
	{
		// printf("--output---\n");
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
           printf("[%s]", strerror(errno)); //error_check
    if (pid == 0)
    {
		execve((*command)->array[0], (*command)->array, env_ll_to_array(*_env));
		printf("[[%s]\n", strerror(errno));		//error_check			
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


/*
** * Dup takes whats in ex. fd[0] and duplicates this to the first free fd. 
** - Tmpin and tmpout: save terminal stdin and terminal stdout for later.
** - Fdin = redirection inputfile or terminal stdin fd[0]
** ** Dup2 takes whats inside an fd and copies this to another fd.
** - Copy fdin to fd[0]. So fd[0] is now redirection inputfile or terminal stdin fd[0]
** - Delete old fdin on fd[5].

** If last node. Fill fdout with redirection outputfile or terminal stdout fd[1]. (! so fdout only filled when last node)
** If pipe, fdin= read-end pipe and  fdout=write end-pipe
*/


void			builtin_another_program(t_command **command, t_env **_env)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, _env);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
		execute_builtin(command, _env);
}



void            execute(t_command **command, t_env **_env)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
		int     i;
        int     len_list;
        int     fdpipe[2];
		int ret;

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
			check_specials(command, *_env);
            dup2(fdin, 0);
            close(fdin);
			/////////////NEW///////////////
			fdout = fill_fdout((*command)->output, tmpout);
			if (((*command)->pipe_after || (*command)->sem) && (*command)->output)
			{
				dup2(fdout,1);
				close(fdout);
				builtin_another_program(command, _env);
			}
			if ((*command)->pipe_after)
			{
				ret = pipe(fdpipe);
				printf("ret pipe = [%d]\n", ret);
                fdout = fdpipe[1];		//write end // wat op fdpipe[1] staat wordt gezet in fdout
                fdin  = fdpipe[0];		//read-end
				// dup2(fdout, fdpipe[1]);
				// close(fdpipe[1]);

				
			}
            dup2(fdout,1);
            close(fdout);
			if (!(*command)->pipe_after && !((*command)->sem && (*command)->output))
				builtin_another_program(command, _env);
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
}


			/////////////OLD WERKEND////////////////
            // if (i == len_list - 1)											//Als in laatste node
            //     fdout = fill_fdout((*command)->output, tmpout);
			
			////////
			// else if ((*command)->sem && (*command)->output)
			// {
			// 	// printf("hier\n");
			// 	fdout = fill_fdout((*command)->output, tmpout);
			// 	dup2(fdout,1);
			// 	close(fdout);
			// 	builtin_another_program(command, _env);
			// }
            // else if ((*command)->pipe_after)              //new
            // {
			// 	// if ((*command)->output)
			// 	// {
			// 	// 	fdout = fill_fdout((*command)->output, tmpout);
			// 	// 	dup2(fdout,1);
			// 	// 	close(fdout);
			// 	// 	builtin_another_program(command, _env);
			// 	// }
            //     pipe(fdpipe);
            //     fdout = fdpipe[1];
            //     fdin  = fdpipe[0];
            // }
            // else                                                        //new (overbodig wel mooier)
            //     fdout = dup(tmpout);
			////////////////////////////////