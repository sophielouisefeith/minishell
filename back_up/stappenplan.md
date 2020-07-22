https://www.gnu.org/software/bash/manual/bash.html#What-is-Bash_003f

• Simple Commands:	  	The most common type of command.
• Pipelines:	    	Connecting the input and output of several commands.

Command:
echo <arguments separated by spaces> 

//
Check for:
1. Builtins
2. <arguments>
3. Control Operators: 
    ; \n |
4. 


//

# control operator
A token that performs a control function:
**newline** 
||
&&
&
**;**       --> Separate commands
;;
;&
;;& 
**|**       --> Pipes
|& 
(
)

# metacharacter
A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.


# ;
Commands separated by a ‘;’ are executed sequentially; the shell waits for each command to terminate in turn. The return status is the exit status of the last command executed.


# Werkwijze real shell:
1. READ:
the shell reads its input and divides the input into words and operators, employing the quoting rules to select which meanings to assign various words and characters.

2. PARSING:
The shell then parses these tokens into commands and other constructs
removes the special meaning of certain words or characters, expands others
redirects input and output as needed, executes the specified command, 
waits for the command’s exit status, 
and makes that exit status available for further inspection or processing.

## 3.1.1 Shell Operation

The following is a brief description of the shell’s operation when it reads and executes a command. Basically, the shell does the following:

1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status).


# Quoting
Quoting is used to remove the special meaning of certain characters or words to the shell. Quoting can be used to disable special treatment for special characters, to prevent reserved words from being recognized as such, and to prevent parameter expansion.

Each of the shell metacharacters (space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.) has special meaning to the shell and must be quoted if it is to represent itself.

Bijv. echo maran ';' echo maran

There are three quoting mechanisms: the escape character, single quotes, and double quotes.


```
mbpvanwillemien:~ maran$ echo $SHELL
/bin/bash
mbpvanwillemien:~ maran$ echo "$SHELL"
/bin/bash
mbpvanwillemien:~ maran$ echo '$SHELL'
$SHELL
```



# Single quotes
Enclosing characters in single quotes (‘'’) preserves the literal value of each character within the quotes

# Double quotes
Enclosing characters in double quotes (‘"’) preserves the literal value of all characters within the quotes

# Simple Commands
It’s just a sequence of words separated by blanks, **terminated by one of the shell’s control operators. --> /n ; |**
**The first word generally specifies a command** to be executed, with the **rest of the words being that command’s arguments.**

# Special parameters
?
($?) Expands to the exit status of the most recently executed foreground pipeline.
In simpler terms, it's the exit status of the last command.

$? is a built-in variable that stores the exit status of a command, function, or the script itself.

$? reads the exit status of the last command executed. After a function returns, $? gives the exit status of the last command executed in the function. This is Bash's way of giving functions a "return value." It returns 0 on success or an integer in the range 1 - 255 on error.


$
($$) Expands to the process ID of the shell. In a () subshell, it expands to the process ID of the invoking shell, not the subshell.




# 3.5.6 Process Substitution
Process substitution allows a process’s input or output to be referred to using a filename. It takes the form of

<(list)
or
>(list)








# 4.1 Bourne Shell Builtins
The following shell builtin commands are inherited from the Bourne Shell. These commands are implemented as specified by the POSIX standard.
◦ cd with only a relative or absolute path
◦ pwd without any options
◦ export without any options
◦ unset without any options

export
export [-fn] [-p] [name[=value]]
Mark each name to be passed to child processes in the environment. If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. The -n option means to no longer mark each name for export. If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed. The -p option displays output in a form that may be reused as input. If a variable name is followed by =value, the value of the variable is set to value.
The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.

unset
unset [-fnv] [name]
Remove each variable or function name. If the -v option is given, each name refers to a shell variable and that variable is removed. If the -f option is given, the names refer to shell functions, and the function definition is removed. If the -n option is supplied, and name is a variable with the nameref attribute, name will be unset rather than the variable it references. -n has no effect if the -f option is supplied. If no options are supplied, each name refers to a variable; if there is no variable by that name, any function with that name is unset. Readonly variables and functions may not be unset. The return status is zero unless a name is readonly.

# 4.2 Bash Builtin Commands
This section describes builtin commands which are unique to or have been extended in Bash. Some of these commands are specified in the POSIX standard.

◦ echo with option ’-n’



# ENV
https://opensource.com/article/19/8/what-are-environment-variables
You can view all environment variables set on your system with the env command.
◦ env without any options and any arguments 

◦ exit without any options

#what does the parser do
• the parser reads whats in the link list and calls to action 
The Parser
The Parser is the software component that reads the command line such as “ls ­al” and puts it 
into a data structure called Command Table that will store the commands that will be 
executed.   

read what is in the link list and then add it to the command table 

A parser is divided into two parts: a Lexical Analyzer or Lexer takes the input characters and 
puts the characters together into words called tokens, and a Parser that processes the 
tokens according to a grammar and build the command table. 