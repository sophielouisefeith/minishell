/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 12:45:40 by maran         #+#    #+#                 */
/*   Updated: 2020/07/13 20:12:09 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Advies Merel: redirections pas op het einde. Dus niet mee verder gegaan. Werkt nog niet helemaal lekker.
*/

void            redirection(t_parse *list, int flag_redirection, int flag_n, char *file_name)
{
    int     fd;
    char    *redirection;

    if (flag_redirection == 1)
    {
        fd = open(file_name,  O_RDWR | O_CREAT | O_TRUNC);
        redirection = ">";
    }
    if (flag_redirection == 2)
    {
        fd = open(file_name,  O_RDWR | O_CREAT | O_APPEND);
        redirection = ">>";
    }
    if (fd == -1)
        error();
    while (ft_strcmp(list->str, redirection))
    {
        write(fd, list->str, ft_strlen(list->str));
        list = list->next;
    }
    close (fd);
}

int             check_redirection(t_parse *list, char **file_name)
{
    int     flag_redirection;

    flag_redirection = 0;
    while (list)
    {
        if (!ft_strcmp(list->str, ">"))
            flag_redirection = 1;
        if (!ft_strcmp(list->str, ">>"))
            flag_redirection = 2;
        if (flag_redirection)
        {
            list = list->next;
            *file_name = list->str;
            break;
        }
        list = list->next;
    }
    return (flag_redirection);
}
