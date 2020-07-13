/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/13 20:15:55 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** First time I have to pass the adress (&head) so the other functions can reach the head value.
*/

void				parser(char *line)
{
	t_parse		*head;
	
	head = NULL;
	ll_split(&head, line, ' ');
	// printf("Parse [%s] [%s] [%s]\n", head->str, head->next->str, head->next->next->str);
	if (!ft_strcmp(head->str, "echo"))
	 	echo(&head);
	else
	{
		write(1, "-bash: ", 7);
		write(1, head->str, ft_strlen(head->str));
		write(1, ": command not found\n", 20);
		
	}
	ll_lstclear(&head);
}
