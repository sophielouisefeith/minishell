/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 13:34:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/15 14:07:02 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void        parser(char *line)
{
    t_list *head; // this is an experiment 
    
    head = NULL;
    printf("in parser\n");
    head = split(line, ' ');
    printf("head[%s]\n", head->data);
    
}