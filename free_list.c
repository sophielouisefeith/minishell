/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/31 20:47:40 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TO DO:
    - Kennelijk hoeven we bij free_input en free_output str_.... niet te freeen. Waarom is dat?
    Is deze niet gemalloct?
    Ik zou verwachten dat we een gemallocte str doorkrijgen vanuit sort. Misschien omdat we deze al in lexer freeen dat het oke is?

** ANTWOORD:
    We hoefte idd niet te freeen omdat we de gemallocte str doorkregen vanuit sort. Consequentie na het freeen van lexer dat we deze gemallocte string dus wel kwijt waren.
    Oplossing: ft_strdup toegevoegd, lexer kan gefreet, str_input en str_output blijven wel bestaan, ze moeten nu ook gefreet worden. 
*/

char			*strdup_and_free(char **str)
{
	char	*tmp;

	tmp = ft_strdup(*str);
	free (*str);
	*str = NULL;
	return (tmp);
}

static void         free_input(t_input *input)
{
	
    t_input       *tmp;

    while(input != NULL)
    {
        tmp = input->next_input;
        free(input->str_input);                          //new
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
        free(output->str_output);                          //new
        free(output);
        output = tmp; 
    }
    output = NULL; 
}

void				free_env(t_env *_env)
{
	t_env		*tmp;

	while (_env)
	{
		tmp = (_env)->next;
		free(_env->name);
		free(_env->value);
		free(_env);
		_env = tmp; 
	}
	_env = NULL; 
}

/*
** TO DO:
    - Beslissen of we de inidividuele arrays binnen **array ook gaan mallocen (net als in split).
    ZO niet, niet freeen. Zo wel freeen! [SOLVED].
*/
		// printf("FREE array[y] = [%p][%s]\n", array[y], array[y]);

void        free_array(char **array)
{
	//printf("-----------------array[Y][%p]\n", array);

	// if (array)
	// 	{
	// 		int n = 0;
	// 		printf("****************************************************array:\n");
	// 		while (array[n])
	// 		{
	// 			printf("node-str[%d] = [%s]\n", n, array[n]);
	// 			n++;
	// 		}
	// 		printf("***********************END**************************array:\n");
	// 	}


	
	//printf("free_array\n");
    int     y;
	int 	temp;
    
    y = 0;
	while(array[y])
		y++;
	temp = y;
	if (y == temp)
	{
		//printf("in array[%d]\n", y);
		while (y > 0)
		{
			//printf("in while \n");
			y--;
			free(array[y]);
		}
		//free(array);
		//array = NULL;
		//return (NULL);
	}
	//printf("backtofreelist\n");
	
	// while(array[y] && array)
	// {
	// 	free(array[y]);
	// 	y++;
	// }
	// array = NULL;
	// free(array);
		
    // while (array[y] && array)
    // {
		
	// 	printf("-----------------array[Y][%p]\n", array[y]);
    //    //free(array[y]);                     //new
	//    printf("-----------------array[NA][%p]\n", array[y]);
    //   // array[y] = NULL;
	//    printf("----------------array[NANU][%p]\n", array[y]);
    //     y++;
    // }
	//free(array);
	//array = NULL;
	// if (array)					//TOEVOEGING TEST?
	// {
	// 	printf("-----------------ARRAY\n");
   	// 	free(array);
	// 	array = NULL;	//
	// }
	
}

/*
** TO DO:
    - Een van mijn eerste tests was kijken of jouw copy maken iets met de leaks te maken had.
    Je mag het terugschrijven naar die variant als je dat prettiger lezen vindt.
    - Zelfde bij input en output.

Mallocs parser:
	- t_command
	- delete_quotes 				*dst 				//new
	- check_path					**patharray			//new
										*patharray[y]
	- fill_builtin_redirec_array	**array
	- allocate_memory_int_string	quote = *int_str
	- Output_fill					*str
	- ll_new_node_output			*new
	- input_fill					*str
	- general						array[y]
*/ 


void        free_list_parser(t_command **command)
{
	////printf("freelistparser\n");
    t_command   *tmp;

    tmp = NULL;
    while (*command)
    {
		//printf("in while loop free list parser\n");
        tmp = (*command)->next_command;
       if ((*command)->array != NULL)
	   {
		   	// tester(NULL, *command);
			free_array((*command)->array);
			free((*command)->array);
			//printf("-------------------------uit-free-array\n");
	   }
		// if ((*command)->quote)						
		// 	free((*command)->quote);			//new		//GEBRUIKEN WE DIE WEL OF NIET?
        if ((*command)->output)
            free_output((*command)->output);
        if ((*command)->input)
            free_input((*command)->input);
       	free(*command);
        *command = tmp;
    }
	//printf("after_free\n");
    *command = NULL;
}

void        free_list_lexer(t_lexer **sort)
{
    t_lexer     *tmp;

    tmp = NULL;
    while (*sort)
    {
        tmp = (*sort)->next_sort;
        if ((*sort)->str)
        	free((*sort)->str);
        if ((*sort)->token)
        	free((*sort)->token);
        free((*sort));
        *sort = tmp; 
    }
    *sort = NULL; 
}


/*
Mallocs in executer:
execute			t_execute *exe;						V
treat_single_quotes
		delete_quotes ->dst							V
		substr			->str						Twijfel (testcases vinden)
treat_double_quotes
		check_backslash_and_dollar
			delete_escape_char		->dst			V
			if_dollar								V
		delete_double_quotes 	->dst				V
		substr					->str				Twijfel (meer testen)
if_no_quote
		delete_escape_char		->dst				V
		delete_escape_char		->dst				V

if_dollar
	t_dollar					-> dollar
	ft_substr					-> dollar->new_str1 en dollar->parameter
	ft_strdup					-> dollar->parameter
	Special_char_found
			strdup				-> dollar->parameter
			itoa				-> dollar->parameter
			ft_substr			-> (*dollar)->parameter	en (*dollar)->new_str2
	join_strings				
			ft_strjoin			->joined
*/


/*
** Onderstaand functie is alleen interessant bij error functies, niet bij regulier freeen.
*/

// void        free_list(t_lexer **sort, t_command **command) 
//     if (sort)
//         free_list_lexer(sort);
//     if (command)
//         free_list_parser(command);
// }