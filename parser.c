/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/08 15:11:31 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** return >0 als echo fout.
** checken return van write?
*/

static int			echo(t_parse *head)
{
	int i;
	int flag_n;

	i = 0;
	flag_n = 0;
	if (head->next)
		head = head->next;
	else
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(head->str, "-n"))
	{
		flag_n = 1;
		head = head->next;
	}
	while (head)
	{
		if (i != 0)
			write(1, " ", 1);
		write(1, head->str, ft_strlen(head->str));
		head = head->next;
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}

void			parser(char *line)
{
	t_parse	*head;
	
	head = NULL;
	ll_split(&head, line, ' ');
	// printf("Parse [%s] [%s] [%s]-\n", head->str, head->next->str, head->next->next->str);
	if (!ft_strcmp(head->str, "echo"))
		echo(head);
	else
	{
		write(1, "-bash: ", 7);
		write(1, head->str, ft_strlen(head->str));
		write(1, ": command not found\n", 20);
		
	}
}
  