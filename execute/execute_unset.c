/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 16:22:20 by maran         #+#    #+#                 */
/*   Updated: 2020/08/25 16:26:20 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Function receives current node and has to delete the next node.
** current's->next has to be relinked.
**      ___________     __________________      _______________________
** -->|current-node|-->|to be deleted-node|-->|to be currents-next-node|
**     ------------     ------------------      -----------------------
**      ___________     ________________________
** -->|current-node|-->|to be currents-next-node|
**     ------------     ------------------------
*/

void	ll_remove_next_node(t_env *list)
{
    t_env *tmp;
    
	if (!list)
		return ;
    tmp = list->next;
    list->next = list->next->next;
    free (tmp->name);
    free (tmp->value);
    free (tmp);
    tmp = NULL;
}

/*
** 1. Check if unset has any arguments, if not return
** 2. Check if argument == head->name
** 3. Check if argument == the following nodes
** TO DO: 
** - Er kunnen meerdere variabelen tegelijk worden geunset.
** Dus straks in een while loop de array argumenten aanleveren.
*/

void        execute_unset(t_env **_env)
{
    t_env *list;
    char unset[] = "_";

    list = *_env;
    if (unset[0] == '\0')
        return ;
    if (!ft_strcmp(list->name, unset))
    {
        (*_env) = (*_env)->next;
        free (list->name);
        free (list->value);
        free (list);
        list = NULL;
        return ;
    }
    while (list->next)
    {
        if (!ft_strcmp(list->next->name, unset))
        {
            ll_remove_next_node(list);
            return ;
        }
        list = list->next;
    }
}
