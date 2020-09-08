/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/09/08 16:35:32 by SophieLouis   ########   odam.nl         */
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

static void		check_old_pwd(t_env **_env, char *old_path)
{
	t_env	*copy_env;
	t_env	*tmp;

	copy_env = *_env;
	while (copy_env)
	{
		if (!ft_strcmp("OLDPWD", copy_env->name))
		{
			copy_env->value = old_path;
			return ;
		}
		copy_env = copy_env->next;
	}
	tmp = ll_new_node_env("OLDPWD", old_path, 1);
	if (tmp == NULL)
		printf("NULL\n");	
	ll_lstadd_back_env(_env, tmp);
}


static void		change_env_pwd(t_env **_env)
{
	t_env	*copy_env;
	char 	*old_path;
	char	*path;

	copy_env = *_env;
	path = getcwd(NULL, 0);													//getcwd malloct if buf == NULL, FREE!
	if (path == NULL)
		strerror(errno);
	while (copy_env)
	{
		if (!ft_strcmp("PWD", copy_env->name))
		{
			old_path = copy_env->value;
			check_old_pwd(_env, old_path);									
			copy_env->value = path;											//FREE
			break ;
		}
		copy_env = copy_env->next;
	}
}

/*
** cd goes to the home directory when:
**	- cd
**	- cd ~/
** cd only reads the first string in the array. When there is a 2nd string
** available it doesn't do anything with it. 
** TO DO:
	- Losse strerror of 1 centrale?
*/

int				execute_cd(t_command *command, t_env **_env)
{
	int		ret;

	ret = 0;
	if (command->array)
	{
		if (!ft_strcmp(command->array[0], "~/"))
		{
			ret = chdir(search_node(*_env, "HOME"));
			if (ret == -1)
				error(command);
			// 	printf("[%s]\n", strerror(errno));
			change_env_pwd(_env);
			return (ret);
		}
		ret = chdir(command->array[0]);
		if (ret == -1)
			error(command);
			// printf("[%s]\n", strerror(errno));
		change_env_pwd(_env);
	}
	else
	{
		ret = chdir(search_node(*_env, "HOME"));
		if (ret == -1)
			error(command);
		change_env_pwd(_env);
	}
	return (ret);
}
