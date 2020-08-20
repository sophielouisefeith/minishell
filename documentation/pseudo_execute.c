/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pseudo_execute.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:43:28 by maran         #+#    #+#                 */
/*   Updated: 2020/08/20 12:32:40 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

 void           execute()
 {
//save in/out
int tmpin=dup(0);                  //maakt een kopie van de fd
int tmpout=dup(1);
 
//set the initial input 
int fdin;
if (infile)                         // check if there is input redirection                                  //ook voor pipe?
    fdin = open(infile,O_READ);      // open the file in bijv. infile and save it in fdin
else                                  // if not: it will create a file descriptor that refers to the default input(0)
// Use default input
    fdin=dup(tmpin);

int ret;
int fdout;
for (i=0;i<numsimplecommands; i++)  //This for loop will create a process for every simple command and it will perform the pipe connections.
{
                                    //In the first iteration, the input of the first simple command will come from fdin (fd[0] of inputredirection)
                                    //Later: fdin will be reassigned to a input pipe later in the loop
//redirect input
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
} //  for                       //END OF FOR LOOP that iterates over all the simple commands

/*
After the for loop executes, all the simple commands are running in their own process and 
they are communicating using pipes
*/


/* restore stdin and stdout to the same file object that was saved in
tmpin, and tmpout. Otherwise, the shell will obtain the 
input from the last file the input was redirected to
*/

//restore in/out defaults                              
dup2(tmpin, 0);
dup2(tmpout, 1);
close(tmpin);              //  close the temporary file descriptors that were used to save the stdin and stdout of the parent shell process
close(tmpout);

//if (!background)      ---> hebben wij niet
// Wait for last command
waitpid(ret, NULL);         //  shell parent process should wait for the last child process in the command to finish before printing the shell prompt
  
} //END OF EXECUTE