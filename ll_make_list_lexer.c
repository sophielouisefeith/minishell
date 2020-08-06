/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
<<<<<<< HEAD:ll_make_list.c
/*   Updated: 2020/08/06 15:26:53 by SophieLouis   ########   odam.nl         */
=======
/*   Updated: 2020/08/06 15:21:54 by maran         ########   odam.nl         */
>>>>>>> 69a9313794baca92cbd6f623d107cdb05e1398e8:ll_make_list_lexer.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer			*ll_new_node(char *str, int *token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
<<<<<<< HEAD:ll_make_list.c
	if(!new)
		error_free(errno);;
	new->str = content;
=======
	if (!new)
		return (0);
	new->str = str;
>>>>>>> 69a9313794baca92cbd6f623d107cdb05e1398e8:ll_make_list_lexer.c
	new->token = token;
	new->next = NULL;
	return (new);
}

/*
** if (list): check if there is already an existing node/list
** 		loop to the back of the list. And set last node->next to the new node
**	No list yet. Set head to the new node.
** We have to make a copy of **head, to not change where the initial head is pointing to: the first node of the list.
*/

void			ll_lstadd_back(t_lexer **sort, t_lexer *new)
{
	t_lexer		*list;

	list = *sort;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*sort = new;
}
