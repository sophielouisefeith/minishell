/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 16:25:50 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// printf("----In parse----\n");
	// printf("----End parse----\n");
	// printf("[%s] [%s] [%s]- ", head->str, head->next->str, head->next->next->str);

void			parse(char *line)
{
	t_parse	*head;
	
	head = ll_split(line, ' ');
}
  