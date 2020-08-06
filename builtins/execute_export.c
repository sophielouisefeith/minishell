/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/08/06 11:30:51 by SophieLouis   ########   odam.nl         */
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

int          check_present_in_env(char *name, char *value, t_env *env)
{
    t_env   *list;

    list = env;
    while (list)
    {
        if (ft_strcmp(name, list->name))
            list = list->next;
        else
        {
            list->value = value;                //past iets aan in ll maar niet aan head
            return (1);
        }
    }
    return (0);
}

static int          check_format(char *str)
{
    int i;
    
    if (!ft_isalpha(str[0]))
    {
        strerror(erroc_notavalidfile);
        // printf("not a valid identifier\n");
        // return (1);
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
        strerror(error_notavalidentifier);
        printf("not a valid identifier\n");
        return (2);                 //foutmelding
    }
}

int             print_declare_x_env(t_env *env)
{
    t_env   *list;
    
    list = env;
    while(list)                                          //misschien beter om eigen printf te gebruiken?
    {
        write(1, "declare-x ", 10);
        write(1, list->name, ft_strlen(list->name));
        write(1, "=", 1);
        write(1, list->value, ft_strlen(list->value));
        write(1, "\n", 1);
        list = list->next;
    }
    return (0);
}

int            execute_export(t_env **env)
{
    t_env   *tmp;
    char    **array;
    int     ret;
    char    str[] = "TEST2=SIEMONS";

    if (str[0] == '\0')
    {
        print_declare_x_env(*env);
        return (0);
    }
    ret = check_format(str);
    if (ret > 0)
        return (1);
    array = ft_split(str, '=');
    if (check_present_in_env(array[0], array[1], *env))
    {
        free(array[0]);
        free_array(array); //andere free voor array
        return (0);
    }
    else
    {
        tmp = ll_new_node_env(array[0], array[1]);
        ll_lstadd_back_env(env, tmp);
    }
    free_array(array);

// // Test in child
//     int id;
//     id = fork();
//     if (id == 0)
//     {
//         printf("--------In child proces--------------\n");
//         execute_env(*env);
//         printf("--------End child---------------------\n");
//     }
// // End tester
    return (0);
}
