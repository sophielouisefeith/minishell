/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/11 17:01:03 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	error_free(int mistake)
{
	if(mistake < 0)
		write(1, strerror(mistake), ft_strlen(strerror(mistake)));
	if(mistake == 103)
	{
		write(1, "error:-------------------------------multiply lines", 50);
		write(1, "-------------------------------\n", 32);
		free_complete(mistake);
		exit(0);
	}
	// if i
    //printf("error[%d]", mistake);
	else
	{
		write(1, "error:-------------------------------", 37);
		//write(1, strerror(mistake), ft_strlen(strerror(mistake)));
		//write(1, "\n", 1);
		write(1, "-------------------------------\n", 32);
		free_complete(mistake);
		exit(0);
	}
	return (0);
}

int	error(int mistake, char *str)
{
	// if i
    //printf("error[%d]", mistake);
	write(1, "error:-------------------------------", 37);
	write(1, strerror(mistake), ft_strlen(strerror(mistake)));
	//write(1, "\n", 1);
	write(1, "-------------------------------\n", 32);
	free(str);
	exit(0);
	return (0);
}
/* System error messageThe strerror() function look up the error message string corresponding to an error number.
The strerror() function accepts an error number argument errnum and returns 
a pointer to the corresponding message string. */


/*errnum 
Is the value of errno to interpret.*/

/* dit moet dan ook  nog gefreed worden    */

//error_free(write(1, strerror(errno), ft_strlen(strerror(errno))));

// int                error_free(write)
// {
//     t_lexer     *lexer;
//     t_command   *command;

//     if(errnum == error_malloc)
//     {
//         write(1,"Malloc failed", 13);
//         // if(lexer)
//         //     free(lexer);
//         // if(command)
//         //     free(command);
//        // exit(1);
//     }

// }
//     if(errnum == erroc_notavalidfile)
//     {
//         write(1,"not a valid file", 16);
//         //exit(1)//   return(2); // dit was denk ik alleen voor de melding dus word waarschijnlijk exti 
//     }

//     if(errnum == error_Multipleline)
//     {
//         write(1,"Multiple line command is not part of the subject", 27);
//        // exit(1);
//     }
//     if(errnum == error_notavalidentifier)
//     {
//         write(1, "not a valid identifier", 22);
//        // return(2); // dit was denk ik alleen voor de melding dus word waarschijnlijk exti 
//     }
    

    
//     exit(1);

    
//}


// int	error_free(int mistake)
// {
//     printf("mistake[%d]", mistake);
// 	write(1, strerror(mistake), ft_strlen(strerror(mistake)));
// 	write(1, "\n", 1);
// 	//free_complete(mistake);
// 	exit(0);
// 	return (0);
// }


//pipe
//free
//input output