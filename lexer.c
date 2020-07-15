/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 17:04:54 by maran         #+#    #+#                 */
/*   Updated: 2020/07/15 22:43:43 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
# define echo 0
# define cd 1 
# define pwd 2
# define export 3
# define unset 4
# define env 5
# define exit 6
*/
// # define builtin 1


static int                check_redirection(char *str)
{
    char    redirection[3][2] = {"<", ">", ">>"};
    int     re_type;
    int     i;

    re_type = -1;
    i = 0;
    while (i < 3 && re_type == -1)
    {
        if(!ft_strcmp(redirection[i], str))
            re_type = i;
        i++;
    }
    return (re_type);
}

static int                check_builtin(char *str)
{
    char    builtin[7][6] = {"echo", "cd", "pwd", "export", "unset", "env",
                                "exit"};
    int     type;
    int     i;

    type = -1;
    i = 0;
    while (i < 7 && type == -1)
    {
        if(!ft_strcmp(builtin[i], str))
            type = i;
        i++;
    }
    return (type);
}

int                lexer(char *str)
{
    int type;
    int semicolon;
    int pipe;
    int re_type;
    
    
    type = -1;
    semicolon = -1;
    pipe = -1;
    re_type = -1;
    
    type = check_builtin(str);
    re_type = check_redirection(str);
    if (!ft_strcmp(";", str));
        semicolon = 1;
    if (!ft_strcmp("|", str))
        pipe = 1;
    if ()
    

    
    
    
    printf("type = %d\n", type);
    
    // char **tokens;
    // tokens = {BUILTIN, {ARGUMENT}, QUOTING, OPERATOR, REDIRECTION, $};
   
}
