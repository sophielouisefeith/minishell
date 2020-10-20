# Used sources:
- https://www.gnu.org/software/bash/manual/bash.html#What-is-Bash_003f
- https://www.geeksforgeeks.org/exit-status-child-process-linux/


# Thanks to:
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


# Remember:
- Simple command: ls, 
- /bin/ls																		
	Als start met ./ of / dan is het een EXECUTABLE of ABSOLUTE PATH VAN EXECUTABLE (bijv. /bin/ls). Als executable dan hoeft path niet gecheck. Kan je meteen gaan executen. Want execve checkt of path bestaat.

/*
** In bash there are multiple functions/special variables/event we don't have to treat. For example:
** echo $! --> process ID (PID), !!, !<anything behind it>
** & --> run in the background, && --> AND, run left and right in sequence.
** echo $$ --> process ID (PID)
** #, echo #, echo $# --> number of arguments
** echo $- --> prints the current set of options in your current shell.
** echo *	--> wildcard
** We don't handle those cases, meaning also no error. To present an error we should know
** all the cases we shouldn't treat. We only treat what the subject tells us to treat.
**/

# Uitgeschreven execute
***************************
** Start positie  		**
***************************
0 XstdinX	"fdin"-[tmpin] 
1 XstdoutX
2 stderror
3 tmpin
4 tmpout
5 XfdinX
6

