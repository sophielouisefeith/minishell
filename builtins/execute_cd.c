/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:31:26 by maran         #+#    #+#                 */
/*   Updated: 2020/07/27 13:55:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>

int             execute_cd()
{
    char s[100]; 
  
    // printing current working directory 
    printf("%s\n", getcwd(s, 100)); 
    // using the command 
    chdir(".."); 
    // printing current working directory 
    printf("%s\n", getcwd(s, 100)); 
    // after chdir is executed 
    return 0;
}