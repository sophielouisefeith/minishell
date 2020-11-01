/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 13:33:20 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static void		check_old_pwd(t_env **_env, char *old_path)
{
	t_env	*copy_env;
	t_env	*tmp;

	copy_env = *_env;
	while (copy_env)
	{
		if (!ft_strcmp("OLDPWD", copy_env->name))
		{
			free(copy_env->value);
			copy_env->value = old_path;
			return ;
		}
		copy_env = copy_env->next;
	}
	tmp = ll_new_node_env("OLDPWD", old_path, 1);
	if (tmp == NULL)
		malloc_fail();
	ll_lstadd_back_env(_env, tmp);
}

static void		change_env_pwd(t_env **_env)
{
	t_env	*copy_env;
	char	*old_path;
	char	*path;

	copy_env = *_env;
	path = getcwd(NULL, 0);
	if (path == NULL)
		strerror(errno);
	while (copy_env)
	{
		if (!ft_strcmp("PWD", copy_env->name))
		{
			old_path = ft_strdup(copy_env->value);
			check_old_pwd(_env, old_path);
			free(copy_env->value);
			copy_env->value = path;
			break ;
		}
		copy_env = copy_env->next;
	}
}

static int		execute_cd_ex(t_command *command,
char *home, t_env **_env, int ret)
{
	if (!ft_strcmp(command->array[0], "~/"))
	{
		home = search_node(*_env, ft_strdup("HOME"));
		ret = chdir(home);
		free(home);
		if (ret == -1)
			error(command);
		change_env_pwd(_env);
		return (ret);
	}
	ret = chdir(command->array[0]);
	if (ret == -1)
		error(command);
	change_env_pwd(_env);
	return (ret);
}

int				execute_cd(t_command *command, t_env **_env)
{
	int		ret;
	char	*home;

	ret = 0;
	home = NULL;
	if (command->array)
		return (execute_cd_ex(command, home, _env, ret));
	else
	{
		home = search_node(*_env, ft_strdup("HOME"));
		ret = chdir(home);
		free(home);
		if (ret == -1)
			error(command);
		change_env_pwd(_env);
	}
	return (ret);
}
