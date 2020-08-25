/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/08/25 12:50:00 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "../minishell.h"

int                execute_pwd(t_command *command, t_env *_env)
{
    char    buf[PATH_MAX];
    char    *path;

    path = getcwd(buf, sizeof(buf));
    if (path == NULL)
        printf("path == -------------------------------------------------------------null\n");
    printf("current path= ------------------------------------------------------- %s\n", path);

    return(0);
}