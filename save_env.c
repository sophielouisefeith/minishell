/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:14:37 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/25 18:48:09 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_env	*ll_new_node_env(char *name, char *value)
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

void		ll_lstadd_back_env(t_env **env, t_env *new)
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

t_env			*save_env(char **env)
{
    t_env	*save_env;
    t_env	*tmp;
    char	**array;
    int		y;

    save_env = NULL;
    y = 0;
    while (env[y])
    {
        array = ft_split(env[y], '=');
        tmp = ll_new_node_env(array[0], array[1]);
        ll_lstadd_back_env(&save_env, tmp);
        array = NULL;
        y++;
    }
    return (save_env);
}
