/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 21:44:18 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/01 16:32:56 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_input(t_input *input)
{
	t_input		*tmp;

	while (input != NULL)
	{
		tmp = input->next_input;
		free(input->str_input);
		input->str_input = NULL;
		free(input);
		input = tmp;
	}
	input = NULL;
}

static void		free_output(t_output *output)
{
	t_output	*tmp;

	while (output != NULL)
	{
		tmp = (output)->next_output;
		free(output->str_output);
		output->str_output = NULL;
		free(output);
		output = tmp;
	}
	output = NULL;
}

void			free_list_parser(t_command **command)
{
	t_command	*tmp;

	tmp = NULL;
	while (*command)
	{
		tmp = (*command)->next_command;
		if ((*command)->array)
			free_array((*command)->array);
		if ((*command)->output)
			free_output((*command)->output);
		if ((*command)->input)
			free_input((*command)->input);
		free(*command);
		*command = tmp;
	}
	*command = NULL;
}
