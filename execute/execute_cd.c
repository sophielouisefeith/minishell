/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/08/25 15:57:05 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

/*
** The chdir command is a system function (system call) which is used to change
** the current working directory. On some systems, this command is used as 
** an alias for the shell command cd. 
** chdir changes the current working directory of the calling process
** to the directory specified in path.
*/

static void		change_env_pwd(t_env **_env)
{
	char	*path;

	path = getcwd(NULL, 0);													//getcwd malloct if buf == NULL, FREE!
	if (path == NULL)
		perror("error with getcwd");
	while (*_env)
	{
		if (!ft_strcmp("PWD", (*_env)->name))
		{
			(*_env)->value = path;											//FREE
			break ;
		}
		*_env = (*_env)->next;
	}
}

static char		*search_node(t_env *_env, char *search)
{
	while (_env)
	{
		if (!ft_strcmp(search, _env->name))
			return (_env->value);
		_env = _env->next;
	}
	return (NULL);
}

/*
** cd goes to the home directory when:
**	- cd
**	- cd ~/
** cd only reads the first string in the array. When there is a 2nd string
** available it doesn't do anything with it. 
*/

void				execute_cd(t_command *command, t_env **_env)
{
	int		ret;

	if (command->array)
	{
		if (!ft_strcmp(command->array[0], "~/"))
		{
			ret = chdir(search_node(*_env, "HOME"));
			if (ret == -1)
				perror("bash: cd:");
			change_env_pwd(_env);
			return ;
		}
		ret = chdir(command->array[0]);
		if (ret == -1)
			perror("bash: cd:");
		change_env_pwd(_env);
	}
	else
	{
		ret = chdir(search_node(*_env, "HOME"));
		if (ret == -1)
			perror("bash: cd:");
		change_env_pwd(_env);
	}
}
