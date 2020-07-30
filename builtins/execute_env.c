/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/07/29 18:46:23 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
extern char	**environ;

t_env			    *ll_new_node_env(char *name, char *value)
{
	t_env		*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void			    ll_lstadd_back_env(t_env **head, t_env *new)
{
	t_env		*list;

	list = *head;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}

void        execute_env(t_env *env)
{
    t_env   *list;

    list = env;
    while (list)                                          //misschien beter om eigen printf te gebruiken?
    {
        write(1, list->name, ft_strlen(list->name));
        write(1, "=", 1);
        write(1, list->value, ft_strlen(list->value));
        write(1, "\n", 1);
        list = list->next;
    }
}

t_env                 *save_env()
{
    t_env       *env;               //head
    t_env       *tmp;
    char        **array;
    int         i;

    env = NULL;
    i = 0;
    while (environ[i])
    {
        array = ft_split(environ[i], '=');
        tmp = ll_new_node_env(array[0], array[1]);
        ll_lstadd_back_env(&env, tmp);
        free (array);
        array = NULL;
        i++;
    }
    printf("env = [%p]\n", env);
    return (env);
}
