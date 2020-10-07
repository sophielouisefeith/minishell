# Used sources:
- https://www.gnu.org/software/bash/manual/bash.html#What-is-Bash_003f
- https://www.geeksforgeeks.org/exit-status-child-process-linux/


# Thanks to:
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


# Remember:
- Simple command: ls, 
- /bin/ls																		
	Als start met ./ of / dan is het een EXECUTABLE of ABSOLUTE PATH VAN EXECUTABLE (bijv. /bin/ls). Als executable dan hoeft path niet gecheck. Kan je meteen gaan executen. Want execve checkt of path bestaat.


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

