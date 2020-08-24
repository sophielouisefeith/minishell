/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:14:37 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/24 13:15:05 by msiemons      ########   odam.nl         */
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

t_env			*save_env()
{
    t_env	*env;
    t_env	*tmp;
    char	**array;
    int		i;

    env = NULL;
    i = 0;
    while (environ[i])
    {
        array = ft_split(environ[i], '=');
        tmp = ll_new_node_env(array[0], array[1]);
        ll_lstadd_back_env(&env, tmp);
        array = NULL;
        i++;
    }
    return (env);
}
