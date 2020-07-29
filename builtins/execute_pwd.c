/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/07/27 17:17:37 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "../minishell.h"

int                 execute_pwd(void)
{
    char    buf[PATH_MAX];
    char    *path;

    path = getcwd(buf, sizeof(buf));
    if (path == NULL)
        printf("path == null\n");
    printf("pwd = %s\n", path);

    return(0);
}