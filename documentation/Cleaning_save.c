/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cleaning_save.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 20:44:43 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 20:05:53 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


Vragen die ik nog heb:

1. Type in lexer, wat als type = Null, whitespace, quote? Loopt gewoon overheen?
2. Worden tokens whitespace, quote, dollar nog gebruikt?
3. Waarvoor gebruiken we: token = allocate_memory_int_string(12); ook alweer? Waarom niet gewoon int token = enum opslaan in node?
Antwoord: wss omdat 1 node meer dan 1 token kan hebben?
4. Check_meta_and_quote:
if ((is_single_quote(line[*i]) || is_double_quote(line[*i])) && line[(*i) - 1] != '\\')

Waarom de toevoeging van != \
Antwoord: omdat als 1 daarvoor \ het niet telt als een closing quote


5. Lijkt alsof we geen tokens meer opslaan voor: quote, dubbel quote, dollar? Klopt dit. Kan de gemallocte string dan weg?

** In int *token is saved what the token type is:
** - General (always)
** - quote, dubbel quote, dollar (optional)


Antwoord:
Wordt iig nog wel gebruikt voor: general, >, >>, ;, | , > , <


6. *str_redirection_dgreater:
Moeten we geen eind teken toevoegen hier?

Antwoord: Voor de test toegevoegd.

7. token[token_redirection]= check_redirections(line, *i, type);

Monitoren of dit goed gaat. Verwarrend stukje.

8. Monitor lexer_utils.c --> 2 aanpassingen gemaakt tijdens cleanen.

9. Vraag bij is_metachar:
** TO DO: 
**  - & en () voor nu eruit gelaten? 			--> Hoeven wij niet toch?

10 Volgens mij gebruiken we Pipe_before nooit? Goed checken bij parser en execute.

11. Gebruiken we command->quote voor iets?

12

-----
MALLOC ERROR IDEAS:
- Grotere GNL buf [Werkt niet]
- Iemand anders GNL?
- Bij is_operator staat de vraag "\n" toevoegen?. Zitten er \n in de zin? Zo ja wat doet dat, is dat een operator? 
			Valt wel onder metachar, want metachar is operator + whitespace.


/***********************
main.c
************************/
/* Removed:
		// g_exit_status = (g_own_exit > 0 && g_own_exit != 999) ?
			// g_own_exit : g_exit_status;
*/

/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
**
** if (line[i] != '\0') --> checks if line is empty.
** If not execute, else new prompt.
** g_own_exit = 0 --> has to be reset.
*/

set_exit_status(); ///-----new // gaat het hier nou mis met./ nee want het is een executable 
g_own_exit = 0;		//Na weghalen toch weer terug gezet vanwege echo "poe


/***********************
GNL.c
************************/
ft_putstr("  \b\b");				//new [Waarom deze line?]

/***********************
Lexer_parser_executer
************************/

// tester(sort, command);

	//if(pipe_status == 12)// slaat nergens op even voor eigen dingen
			//printf("malloc failed\n"); /// dit is overbodig word al een error gegeven en gefreet omdat g_own_exit =1 

/*
** We loop through sort in parser, we make a copy beforehand.
** So when we start free'ing, we start at the first node of sort and not at the end.
** TO DO:
	- Wss ook nog een copy van command nodig na execute. Later naar kijken. [Check]
*/

if (line[i] != '\0')			---> Verwijderd, volgens mij checken we hier al op.
		lexer(&sort, line);



/***********************
Lexer
************************/

/*
** Changelog:
** - Getest:
	Type meegeven aan save_word. Kan niet want je moet halverwege een word ook checken op " (bijv. Hoi"maran).
	Type moet dus niet vast staan vooraf.
** - Verwijderd:
	type == token_quote || type == token_dquote
*/

/***********************
Check_meta_and_quote
************************/
** Meanwhile check for:
** 	- dollar-signs between the quotations

/*
** While it's not a separating character (metacharacter) it checks every char
** for quotation marks and dollar-signs.
** 	- quotation: check if there is a closing quotation. If not: the real bash shell
** would act as a multiple line command. This not part of the subject.
*/

/***********************
Save_operator
************************/

/*
** Changelog:
** 	- Aangepast:
	 11 -> 12. Was er een reden voor mallocen andere size (12) 
	 voor int *token dan bij save_word (11)?	[IK DENK HET NIET --> 12]
	- New check_redirections v.w ls >>>>>>>>>>> file. De oude  token[token_redirection] = 1; wordt nu gereturned door de functie.
*/

/***********************
*Lexer_utils
************************/

/*
** Changelog:
** - Verwijderd:
	if (is_whitespace(line[*i]))
		return (token_whitespace);
	if (is_single_quote(line[*i]))
		return (token_quote);
	else if (is_double_quote(line[*i]))
		return (token_dquote);
** - Aangepast:
	if (is_operator(line[*i]))
		return (is_operator(line[*i]));
*/



/***********************
*str_redirection_dgreater
************************/

/*
** Changelog:
   - Veranderd ivm malloc error
   	// str = ">>";
*/


/***********************
*allocate memory int string
************************/
int				*allocate_memory_int_string(int i)
{
	int 	*int_str;

	int_str = (int *)malloc(sizeof(int) * i);				//Calloc ipv bzero?		--> AANGEPAST						
	ft_bzero(int_str, i * sizeof(int));
	return (int_str);
}

/***********************
* Check_redirections
************************/
/*
** Returns 1 because token[token_redirection] has to be on 1.
*/

/***********************
* Character_check.c
************************/
/***********************
* is_operator
************************/
/*
** & and quotes are accepted characters in words.
** To do:
**  - \n nog toevoegen?
*/

/***********************
* is_metachar
************************/
/*
** A metacharacter:
** 			- A character that, when unquoted, separates words.
**			A metacharacter is a whitespace, or one of the following
**			characters: | & ; ( ) < >
** TO DO: 
**  - & en () voor nu eruit gelaten? 
*/

/***********************
* ll_make_list_lexer.c
************************/

/*
** if (list): check if there is already an existing node/list
** 	loop to the back of the list. And set last node->next to the new node
**	No list yet. Set head to the new node.
** We have to make a copy of **head, to not change where the initial head is pointing to: the first node of the list.
*/


===========================================
PARSER
===========================================

/*
** Changelog:
	- Veel gereorganiseerd, check github < 13-08-2020 voor versie hiervoor.
*/

=====================
fill_builtin_redirec_array
=====================
MOET VEEL KORTER!

		// quote = allocate_memory_int_string(num_nodes);			//VERWIJDERD!				//GBERUIKEN WE DEZE NOG?

	if ((*tmp)->builtin >= builtin_echo && (*tmp)->builtin <= builtin_exit)			//dit kan evt ook in count_node
		*sort = (*sort)->next_sort;
	---------> Verplaatst naar count node zoals gesuggereerd.
	Daarvoor van count_node( **sort, ...) moeten maken.

Oude count_node:

// int				count_node(t_lexer *sort, int type_builtin)
// {
// 	int 	i;

// 	i = 0;
// 	while (sort && !sort->token[token_pipe] && !sort->token[token_semicolon])
// 	{
//         if (sort->token[token_general])
// 		    i++;
//         if (sort->token[token_redirection])
// 		    sort = sort->next_sort;
//         sort = sort->next_sort;
// 	}
// 	if (type_builtin >= builtin_echo && type_builtin <= builtin_exit)
// 		i--;
// 	return (i);
// }


/***********************
* Close_and_save_array
************************/

Verwijderd:
	// (*tmp)->quote = quote;				//Twijfel waarvoor we dit gebruikten


/***********************
*  General
************************/

/*
** Changelog:
	- Changed:
	array[*y] = (*sort)->str;
	- Removed 08/09:
			// newstr = trunc_quotes((*sort)->str);		--> worden nu al definitief verwijderd in check_builtin_node
			// array[*y] = newstr;
	- Added 29/09 (na vak): 
			(*sort)->str = trunc_quotes((*sort)->str);	--> Kan niet al worden verwijderd in check_builtin_node,
			want als een builtin dan gaat hij al naar de volgende node. Dus "hallo", komt nooit meer in check_builtin_node.
			Lelijke structuur. Maar voor nu even weer hersteld naar soort van de oude variant.
	- Remove vanwege new_trunc structure:
		// if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
		// {
		// 	(*sort)->str = trunc_quotes((*sort)->str);
		// 	quote[*y] = ((*sort)->token[token_quote]) ? token_quote : token_dquote;			//new //Weet niet meer waarvoor dit was, wel belangrijk denk ik?
		// }
	
*/

LET OP: Verwijderd: Is wel het quote mysterie.. gebruiken we het of niet?

	// if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
		// {
		// 	(*sort)->str = trunc_quotes((*sort)->str);
		// 	quote[*y] = ((*sort)->token[token_quote]) ? token_quote : token_dquote;			//new //Weet niet meer waarvoor dit was, wel belangrijk denk ik?
		// }

 while (*sort && (*sort)->token[token_general]) 			//dit er nog bij?  && array != NULL)

/*
** Changelog 09/09:
	- Count node heringericht zoday we ? konden deleten.
 	-delete:  num_nodes = ((*tmp)->builtin == builtin_no_com || (*tmp)->builtin == builtin_no) ? (num_nodes + 1) : num_nodes;			//new	//in count_nodes fixen?
** 	- Verplaatst van check_builtin_node naar fill_builtin.....: 
	if ((*tmp)->builtin >= builtin_echo && (*tmp)->builtin <= builtin_exit)			//dit kan evt ook in count_node
			*sort = (*sort)->next_sort;
** OLD (fixed ls before) 
** num_nodes + 1:
** This is needed in cases of no builtin. The non-builtin needs to be saved in the array,
** because execve needs this to read it out. The builtins are not saved in the array because
** we use a builtin_type to save the type.
*/

