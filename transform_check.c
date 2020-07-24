/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/24 16:11:32 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char           *trunc_quotes(t_lexer *list,char *str)
{
    int     len;
    // t_command **commandstr;
    char       *newstr;
    len = ft_strlen(str);
    
    len = len - 2;
	newstr= ft_substr(list->str, 1, len);
    return(newstr);
}