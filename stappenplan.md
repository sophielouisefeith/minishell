#parser


0. THE HEAD:

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>IF THE HEAD {NODE 0} != BUILTING
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a      		whitespace					result
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
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a ' '  		s qoute
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







>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a " "  		d qoute



>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a | or ; 		pipe or semicolom
<note> a head node never can be a | or ;
the result always will be 

<bash: syntax error near unexpected token `|'>

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a >  			greater


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a >> d 		greater


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>with a <    		lesser




<conclusion>

• if the head is not a builtin then check if it the head is a | pipe or ; semicolum. 
if yes 
>>ten return : <bash: syntax error near unexpected token `|'>  or  <bash: syntax error near unexpected token `;'>

• if the head is not a builtin and is not a | pipe or  semicolum ;
then check if head->next == | ||  head->next == ;
>> if not then return <bash:   : command not found>




>> input
>> output 

get_nextlin_ standard output 

command line input echo hallo daar 
command line output > 



-----------------------------
-----------------------------
-----------------------------
-----------------------------







1. | PIPE 

>> How does the pipe works  
>> Definition of the pipe, Connecting the input and output of several commands. this depends on the builtin. 
>> if head ==  (cd || env || pwd || env || unset || exit) and head->next == | 
then only take the head->next[3] node but if head->next[4] == | then  go to head->next[5]
>> Combination of  cd | pwd then works both. 




2. ;
3. " ""
4. ""
5. >>
6. >
7. < >