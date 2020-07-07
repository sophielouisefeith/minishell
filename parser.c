/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 18:55:21 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static void			echo(t_parse *head)
// {
	
// 	if (ft_strcmp(head->str, "-n"))
// 		printf("-n found\n");
// 	else
// 	{
// 		while (head)
// 		{
// 			write(1, head->str, ft_strlen(head->str));
// 			head = head->next;
// 		}
// 	}
// }

void			parse(char *line)
{
	t_parse	*head;
	
	head = NULL;
	printf("----In parse----\n");
	ll_split(&head, line, ' ');
	printf("Parse [%s] [%s] [%s]-\n", head->str, head->next->str, head->next->next->str);
	printf("----End parse----\n");
	
	// if (ft_strcmp(head->str, "echo"))
	// {
	// 	printf("JEP ECHO");
	// }
	// 	// echo(head);
		
}
  