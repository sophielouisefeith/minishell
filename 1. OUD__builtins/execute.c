// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   execute.c                                          :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: maran <maran@student.codam.nl>               +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
// /*   Updated: 2020/08/14 10:09:19 by maran         ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

/*
** to do:
	// pipe     //buf ontvangen voor de pipe gaan we het wel of niet meegeven, bijv in echo geven we het niet meer 
    //sem
*/

/*
** Changelog:
	//changed next to  next_sort
*/

static char             *execute_builtin(t_command **command)
{

    char *buf;
    t_env *env;                         //kopie head
    env = save_env();

    // printf("env = [%p]\n", env);
    // printf("--------ENV BEFORE---------\n");
    // execute_env(env);
    if ((*command)->builtin == builtin_echo)
        buf = execute_echo(command);
    if ((*command)->builtin == builtin_cd)
        execute_cd();
    if ((*command)->builtin == builtin_pwd)
        execute_pwd();
    if ((*command)->builtin == builtin_env)
        execute_env(env); //buf.
    if ((*command)->builtin == builtin_export)
        execute_export(&env);
    if ((*command)->builtin == builtin_unset)
        execute_unset(&env);
    if ((*command)->builtin == builtin_exit)
        execute_exit();
    // printf("--------ENV AFTER---------\n");
    // execute_env(env);
    return (buf);
}

/*
** Tel aantal nodes. Aantal nodes is aantal processen
** ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts, met enters ertussen
** | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
** > 
*/

/*
** id == 0, dan zit je in child.
*/

static int            execute_pipe(t_command **command)
{
    int fd[2];
    int id;
    int ret;

    if (pipe(fd) == -1)
    {
        printf("ERROR in opening the pipe\n");
        return (1);
    }
    id = fork();
    if (id == -1)
        printf("ERROR with fork\n");
    if (id == 0)                                                        //child
    {
        close(fd[0]);
        char *buf;
        ret = write(fd[1], buf, ft_strlen(buf));
        if (ret == -1)
            printf("ERROR in write\n");
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char *buffer;
        buffer = (char *)malloc(sizeof(char) * 1024);
        // buf = execute_builtin(command, buf);
        ret = read(fd[0], buffer, 1024);                               //lees van fd[0] en sla op in buffer
        if (ret == -1)
            printf("ERROR in read\n");
        printf("In parent proces: > via pipe van child proces ontvangen [%s]\n", buffer);
        close(fd[0]);
    }
    return (0);   
}

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

static void            trial(t_command *command)
{
        int             fd[0];
        t_input         *input;
        t_output        *output;
        int             fdin;
        int             fdout;
        // char            *tmpin;
        // char            *tmpout;
        int            tmpin;
        int            tmpout;
        int             i;
        int             lennode;
        int             fdpipe[2];
        int             ret;


        i = 0;
        lennode = lstsize(command);
        tmpout = output->str_output; //= dub(0);
        tmpin = input->str_input;   //= dub(1);

        tmpin =   dub(0);
        tmpout  = dub(1);


        if(input->str_input)
            fdin = open(input->str_input, UIO_READ);
        else
        {
            fdin = dub(tmpin);
        }

        
        while(i < lennode)
        {
            //redirect input is dit dus waar we de kindjes redirection 
            i++;
            dup2(fdin, 0);
            close(fdin);
            
            if( i == lennode -1 )
            {
                if(output->str_output)
                {
                    fdout=open(output->str_output, UIO_READ );   // dit moet iets anders worden
                }
                else
                fdout = dub (tmpout);
            }
            else
            {
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }

            dup2(fdout,1);
            close(fdout);

            ret = fork();
            if(ret == 0)    //niew childprocess ?
            {
               // execve(command->next_command, command->next_command, command->next_command);    //Scom simple command 
                execve(input->str_input, &output->str_output, &output->str_output);    ///
                perror("execve");
                exit(1);
            }

        }  
            dup2(tmpin, 0); //,0
            dup2(tmpout, 1); //,1
            close(tmpin);
            close(tmpout);
        

       

        // if(!background)  // geen background gebruiken maar om nu in de parent te komen 
        // {
        //     //wait for last command  // this is were the parrent comes in then
        //     waitpid(ret, NULL);
        // }

}





int             execute(t_command **command)
{
    char *buf;
    int     i;

    i = lstsize(*command);
   // pipe before and pipe after. 
    while(command)
    {
        buf  = execute_builtin(command);
        // command = command->next;
        if ((*command)->pipe_after)
            buf = execute_pipe(command);
    }
    //write(fd, buf,)
    return (0);
}

