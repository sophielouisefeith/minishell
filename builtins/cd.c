/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:15:18 by maran         #+#    #+#                 */
/*   Updated: 2020/07/24 14:24:09 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int         main(int argc, char **argv)
{
    // int ret;
    
    // ret = chdir(argv[1]);
    // if (ret == -1)
    //     printf("error in chdir\n");
    

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