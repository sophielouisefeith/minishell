/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/17 12:27:52 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TO DO:
    - Kennelijk hoeven we bij free_input en free_output str_.... niet te freeen. Waarom is dat?
    Is deze niet gemalloct?
    Ik zou verwachten dat we een gemallocte str doorkrijgen vanuit sort. Misschien omdat we deze al in lexer freeen dat het oke is?
*/

static void         free_input(t_input *input)
{
    t_input       *tmp;

    while(input != NULL)
    {
        tmp = input->next_input;
        free(input);
        input = tmp; 
    }
    input = NULL;
}

static void         free_output(t_output *output)
{
    t_output	   *tmp;

    while (output != NULL)
    {
        tmp = (output)->next_output;
        free(output);
        output = tmp; 
    }
    output = NULL; 
}

/*
** TO DO:
    - Beslissen of we de inidividuele arrays binnen **array ook gaan mallocen (net als in split).
    ZO niet, niet freeen. Zo wel freeen! [SOLVED].
*/

void        free_array(char **array)
{
    int     y;
    
    y = 0;
    while (array[y])
    {
        free(array[y]);                     //new
        array[y] = NULL;
        y++;
    }
    free(array);
}

/*
** TO DO:
    - Een van mijn eerste tests was kijken of jouw copy maken iets met de leaks te maken had.
    Je mag het terugschrijven naar die variant als je dat prettiger lezen vindt.
    - Zelfde bij input en output.
*/ 

void        free_list_parser(t_command **command)
{
    t_command   *tmp;

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

void        free_list_lexer(t_lexer **sort)
{
    t_lexer     *tmp;

    tmp = NULL;
    while(*sort)
    {
        tmp = (*sort)->next_sort;
        if((*sort)->str)
            free((*sort)->str);
        if((*sort)->token)
            free((*sort)->token);
        free((*sort));
        *sort = tmp; 
    }
    *sort = NULL; 
}

/*
** Onderstaand functie is alleen interessant bij error functies, niet bij regulier freeen.
*/

// void        free_list(t_lexer **sort, t_command **command) 
//     if (sort)
//         free_list_lexer(sort);
//     if (command)
//         free_list_parser(command);
// }