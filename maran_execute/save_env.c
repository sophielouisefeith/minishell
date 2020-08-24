/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:14:37 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/24 15:31:12 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
extern char	**environ;

static t_env	*ll_new_node_env(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

static void		ll_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
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
