#parser


0. THE HEAD:

IF THE HEAD {NODE 0} != BUILTING


with a      		whitespace					result
•••••••••••••••••••••••••••••••••••••••••••••••••••• echo	
bash-3.2$         echo hallo																		*works normal			
hallo
•••••••••••••••••••••••••••••••••••••••••••••••••••• cd
bash-3.2$         cd																				*works normal
•••••••••••••••••••••••••••••••••••••••••••••••••••• pwd
bash-3.2$                pwd																		*works normal
/Users/sfeith
•••••••••••••••••••••••••••••••••••••••••••••••••••• export
bash-3.2$                export
declare -x Apple_PubSub_Socket_Render="/private/tmp/com.apple.launchd.hyc4EJfGMU/Render"			*works normal
•••••••••••••••••••••••••••••••••••••••••••••••••••• env
bash-3.2$ env																						*works normal
TERM_PROGRAM=vscode
TERM=xterm-256color
•••••••••••••••••••••••••••••••••••••••••••••••••••• unset
bash-3.2$ unset pwd																					*works normal
bash-3.2$ 
•••••••••••••••••••••••••••••••••••••••••••••••••••• exit
bash-3.2$          exit																				*works normal
exit
➜  maranshell git:(parser) ✗ 
with a ' '  		s qoute
•••••••••••••••••••••••••••••••••••••••••••••••••••• echo	
bash-3.2$ ' ' echo hallo																			<command not found>
bash:  : command not found

<note> 		: if there is a | or ;  involved, it will error on the first comman but 				<if there is a | or ;>
will read the second comman
*example 	: 
bash-3.2$ ' ' | echo hallo
bash:  : command not found
hallo
bash-3.2$ ' ' ; echo hallo
bash:  : command not found
hallo
•••••••••••••••••••••••••••••••••••••••••••••••••••• cd
bash-3.2$ ' ' cd																					<command not found>
bash:  : command not found



												*works normal
•••••••••••••••••••••••••••••••••••••••••••••••••••• pwd
bash-3.2$                pwd																		*works normal
/Users/sfeith
•••••••••••••••••••••••••••••••••••••••••••••••••••• export
bash-3.2$                export
declare -x Apple_PubSub_Socket_Render="/private/tmp/com.apple.launchd.hyc4EJfGMU/Render"			*works normal
•••••••••••••••••••••••••••••••••••••••••••••••••••• env
bash-3.2$ env																						*works normal
TERM_PROGRAM=vscode
TERM=xterm-256color
•••••••••••••••••••••••••••••••••••••••••••••••••••• unset
bash-3.2$ unset pwd																					*works normal
bash-3.2$ 
•••••••••••••••••••••••••••••••••••••••••••••••••••• exit
bash-3.2$          exit																				*works normal
exit
➜  maranshell git:(parser) ✗ 







with a " "  		d qoute



with a | or ; 		pipe or semicolom
<note> a head node never can be a | or ;
the result always will be 

<bash: syntax error near unexpected token `|'>

with a >  			greater


with a >> d 		greater


with a <    		lesser




<conclusion>

• if the head is not a builtin then check if it the head is a | pipe or ; semicolum. 
if yes 
ten return : <bash: syntax error near unexpected token `|'>  or  <bash: syntax error near unexpected token `;'>

• if the head is not a builtin and is not a | pipe or  semicolum ;
then check if head->next == | ||  head->next == ;
if not then return <bash:   : command not found>




input
output 

get_nextlin_ standard output 

command line input echo hallo daar 
command line output > 



-----------------------------
-----------------------------
-----------------------------
-----------------------------







1. <h1> | PIPE </h1> 

<h2>How does the pipe works </h2>
<p>Definition of the pipe, Connecting the input and output of several commands. this depends on the builtin. 
if head ==  (cd || env || pwd || env || unset || exit) and head->next == | 
then only take the head->next[3] node but if head->next[4] == | then  go to head->next[5]
Combination of  cd | pwd then works both. </p>




2. ;
3. " ""
4. ""
5. >>
6. >
7. < >


<h1>Input and Output.</h1>



<h2> <b>INPUT</b> </h2>
<h4>When we say Input, it means to feed some data into a program. An input can be given in the form of a 
file or from the command line. C programming provides a set of built-in functions to read the given input and feed it to the program as per requirement</h4>

<h2> OUTPUT </h2>
<h4>When we say Output, it means to display some data on screen, printer, or in any file. </h4>


<p>C programming provides a set of built-in functions to output the data on the computer 
screen as well as to save it in text or binary files.
The Standard Files C programming treats all the devices as files. 
So devices such as the display are addressed in the same way as files 
and the following three files are automatically opened when a program executes to provide access to the keyboard and screen.</h2>


In the following descriptions, if the file descriptor number is omitted, and the first character of the redirection operator is ‘<’, 
the redirection refers to the standard input (file descriptor 0). If the first character of the redirection operator is ‘>’, 
the redirection refers to the standard output (file descriptor 1).

if you have > you get the output from the input -- shows the input
if you have < you get the input from the output ->> to the output. 



pwd cd 

na | geen output 
van de input >




<h1> pipeline</h1>
<h2> pipeline is a mechanism for inter-process communication using message passing.></h2>

Command is entered and if length is non-null, keep it in history.
Parsing : Parsing is the breaking up of commands into individual words and strings
Checking for special characters like pipes, etc is done
Checking if built-in commands are asked for.
If pipes are present, handling pipes.
Executing system commands and libraries by forking a child and calling execvp.
Printing current directory name and asking for next input.

The parser then, concerns itself with the context in which each token appears, which is a way of saying it cares about whether or not the sequence and combination of tokens actually detected fits the expected grammar.

echo leest niet van de stinp



SYNOPSIS
     #include <unistd.h>

     int
     execve(const char *path, char *const argv[], char *const envp[]);

DESCRIPTION
     execve() transforms the calling process into a new process.  The new process is constructed from an ordinary file, whose name is pointed to by path, called the new process file.  This file is either an executable object file,
     or a file of data for an interpreter.  An executable object file consists of an identifying header, followed by pages of data representing the initial program (text) and initialized data pages.  Additional pages may be speci-
     fied by the header to be initialized with zero data;  see a.out(5).

     An interpreter file begins with a line of the form:

           #! interpreter [arg ...]

     When an interpreter file is execve()'d, the system runs the specified interpreter.  If any optional args are specified, they become the first (second, ...) argument to the interpreter. The name of the originally execve()'d
     file becomes the subsequent argument; otherwise, the name of the originally execve()'d file is the first argument.  The original arguments to the invocation of the interpreter are shifted over to become the final arguments.
     The zeroth argument, normally the name of the execve()'d file, is left unchanged.




echo $*hallo                                 
echo $A*aap
echo  $\$

echo $5hallo                  check

oke dus wanneer bestaat hij niet 
dan moet hij ergens in en het eerste dingetje weghalen

alle tekst na niet bestaande of geldige $





ERROR 

no closing qoute 
 unexpected EOF while looking for matching `"'
bash: syntax error: unexpected end of file

