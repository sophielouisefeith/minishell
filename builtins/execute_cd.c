/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/08/24 16:08:55 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include "../minishell.h"
#include <unistd.h>
#include <limits.h>




/*
The chdir command is a system function (system call) which is used to change the current working directory. On some systems, this command is used as an alias for the shell command cd. 
chdir changes the current working directory of the calling process to the directory specified in path. 

oplossen cd ~/
*/

int             execute_cd(t_command *command)
{
	char    buf[PATH_MAX];
	char 	*path;
	int  	tmp;
	

	if(command->array)
	{
		tmp = chdir(*command->array);
		if(tmp == -1)
			perror("error\n");
	}
	else
	{
		chdir("..");
	}
	path = getcwd(buf, sizeof(buf));                      //FREE
		if(path == NULL)
			perror("error");
	printf("now the path is changed -------------------------------------------------------  \n[%s]\n", path);
    return 0;
}