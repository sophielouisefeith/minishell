/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/07/28 18:38:10 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Export command is used to export a variable to the environment 
** of all the child processes running in the current shell.
**
** 1. Check of voldoet aan formar name=value
        - eerste char moet char zijn
        - er kunnen geen speciale chars in name zitten BEHALVE underscore
        - geen = dan gebeurt er niets
        - wel = dan var aangemaakt 
** 2. Check of al in env zit
**   zo ja --> verander value
**   zo nee --> maak nieuw aan
** 
** TO DO:
** Child processes nu ook al gecovered? Uitzoeken.
*/

static int          check_format(char *str)
{
    int i;
    
    if (!ft_isalpha(str[0]))
    {
        printf("not a valid identifier\n");
        return (1);
    }
    i = 1;
    while ((ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_') && str)
        i++;
    if (str[i] == '=')
        return (0);                 //maak var aan
    else if (str[i] == '\0')
        return (1);                 //doet niets
    else
    {
        printf("not a valid identifier\n");
        return (2);                 //foutmelding
    }
}

/*
** have to make a copy of *env otherwise the env is not pointing to 
** the beginning of the list anymore.
*/

int          check_present_in_env(char *name, char *value, t_env **env)
{
    t_env   *list;
    
    list = *env;
    while (list)
    {
        if (ft_strcmp(name, list->name))
            list = list->next;
        else
        {
            list->value = value;
            return (1);
        }
    }
    return (0);
}

int            execute_export(t_env **env)
{
    t_env   *tmp;
    char    **array;
    int     ret;
    char    str[] = "test=123";

    ret = check_format(str);
    if (ret > 0)
        return (1);
    array = ft_split(str, '=');
    if (check_present_in_env(array[0], array[1], env))
    {
        free (array[0]);
        free (array);
        return (0);
    }
    else
    {
        tmp = ll_new_node_env(array[0], array[1]);
        ll_lstadd_back_env(env, tmp);
    }
    free (array);
    return (0);
}
