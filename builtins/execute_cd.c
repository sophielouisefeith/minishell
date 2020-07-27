/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/07/27 17:17:29 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include "../minishell.h"

int             execute_cd()
{
    chdir("..");
    return 0;
}