/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_maran.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 10:06:46 by maran         #+#    #+#                 */
/*   Updated: 2020/08/20 10:38:39 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void           execute(t_command **command)
{
int tmpin=dup(0);                  //dup takes what is in fd (0)
int tmpout=dup(1);
int fdin;
int ret;
int fdout;
int i;

if (infile)                         // check if there is input redirection                                  //ook voor pipe?
    fdin = open(infile,O_READ);      // open the file in bijv. infile and save it in fdin
else                                  // if not: it will create a file descriptor that refers to the default input(0)
    fdin=dup(tmpin);

i = 0;
while(i < num_commands)
{
    dup2(fdin, 0);                  //Maakt kopie van gespecificeerde fd. 
                                    //Redirects the standard input to come from fdin.
                                    //After this any read from stdin will come from the file pointed by fdin
    
    close(fdin);                    //close because fd no longer needed

//setup output
    if (i == numsimplecommands­)   //checks if this iteration corresponds to the last simple command // Last simple command 
    {
                                  // will make sure that fdout is a file descriptor for the output in the last iteration.
                                
        if(outfile)                //if there is a output file redirection, assign it to fdout
            fdout=open(outfile, O_READ);
        else
                                    // Else create a new file descriptor that points to the default output // Use default output 
            fdout=dup(tmpout);
    }
    else                            //Als niet laatste ronde/laatste commando: the output will be a pipe and not a file
    {
        int fdpipe[2];              //create pipe
        pipe(fdpipe);               //create pipe
    
        fdout=fdpipe[1];            //(write to) fdpipe[1] is assigned to fdout
        fdin=fdpipe[0];             //(read from) fdpipe[0] is assigned to fdin
/*
** fdin=fdpipe[0] --> the core of the implementation of pipes!
** Since it makes the input fdin of the next simple command in the next iteration
** to come from fdpipe[0] of the current simple command.
*/
    }
    // Redirect output
    dup2(fdout,1);                   //redirect the stdout to go to the file object pointed by fdout
                                    //After this line, the stdin and stdout have been redirected to either a file or a pipe
    close(fdout);                   //closes fdout that is no longer needed.


 // Create child process            // the input and output redirections for the current simple command are already set
    ret = fork();                   // forks a new child process that will inherit the file descriptors 0,1, and 2
                                    // that correspond to stdin, stdout, and stderr, that are redirected to either the terminal, a file, or a pipe.                


    if(ret==0)
    {
        execvp(scmd[i].args[0], scmd[i].args);   // calls the execvp() system call that loads the executable for this command.
                                                // If execvp succeeds it will not return. 
        perror(“execvp”);
        _exit(1);
/*
This is because a new executable image has been loaded in the current CHILD process and the memory has been 
overwritten, so there is nothing to return to. 
*/
    }
}
