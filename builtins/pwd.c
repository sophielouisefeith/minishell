/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/07/24 13:41:38 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <limits.h>

int          main(void)
{
    char buf[PATH_MAX];
    char *ptr;

    ptr = getcwd(buf, sizeof(buf));
    if (ptr == NULL)
        printf(" ptr == null\n");
    printf("ptr = %s\n", ptr);

    return(0);
}