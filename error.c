/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/06 11:11:19 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* System error messageThe strerror() function look up the error message string corresponding to an error number.
The strerror() function accepts an error number argument errnum and returns 
a pointer to the corresponding message string. */


/*errnum 
Is the value of errno to interpret.*/

char                *strerror(int errnum)
{

    if(errnum == error_malloc)
    {
        write(1,"Multiple line command is not part of the subject", 27);
       // exit(1);
    }

    
    if(errnum == erroc_notavalidfile)
    {
        write(1,"not a valid file", 16);
        //exit(1)//   return(2); // dit was denk ik alleen voor de melding dus word waarschijnlijk exti 
    }

    if(errnum == error_Multipleline)
    {
        write(1,"Multiple line command is not part of the subject", 27);
       // exit(1);
    }
    if(errnum == error_notavalidentifier)
    {
        write(1, "not a valid identifier", 22);
       // return(2); // dit was denk ik alleen voor de melding dus word waarschijnlijk exti 
    }
    

    
    exit(1);

    
}