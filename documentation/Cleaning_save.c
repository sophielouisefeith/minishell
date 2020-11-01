/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cleaning_save.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 20:44:43 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 17:02:24 by msiemons      ########   odam.nl         */
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

12 Gaat het goed met doorpassen van adres van tmp->array naar general?

------------------
MALLOC ERROR IDEAS:
- Grotere GNL buf [Werkt niet]
- Iemand anders GNL?
- Bij is_operator staat de vraag "\n" toevoegen?. Zitten er \n in de zin? Zo ja wat doet dat, is dat een operator? 
			Valt wel onder metachar, want metachar is operator + whitespace.

-----------------



13. CBA: moet die nog andere if_dollar?












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



Backup:
static void		fill_builtin_redirec_array(t_lexer **sort, t_command **tmp, t_env **_env)
{
	//printf("fill_builtin_redirec_array--------parser\n");
	char 		**array;
	int 		*quote;
	int 		num_nodes;
	int			ret;
    int 		y;

	array = NULL;
	quote = NULL;
	num_nodes = 0;
	y = 0;
	(*tmp)->builtin = check_builtin_node(sort, _env);
	num_nodes = count_node(sort, (*tmp)->builtin);
	if (num_nodes > 0)
	{
		array = (char **)malloc((num_nodes + 1) * sizeof(char *));
		if (array == NULL)
			malloc_fail();
	}
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
		ret = general(sort, array, &y);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
	}
	return (close_and_save_array(tmp, array, y));
}



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

-----------------------
Parser_utils.c
------------------------

/***********************
* check_builtin_node
************************/

	// printf("(*sort)->str = [%s]\n", (*sort)->str);
	// printf("(*sort)->str = [%s]\n", (*sort)->str);


	if (is_single_quote((*sort)->str[0]) || is_double_quote((*sort)->str[0]))		//mag alleen bij het eerste woord worden getrunct (hoezo komt hij niet bij volgende woorden?)

	Voor verplaatsen check path:
	// char 	*str_before;
	
	// if (builtin_type == builtin_no)
	// {
	// 	str_before = (*sort)->str;	//Wanhoop: mag dit want stack? of strdup?
	// 	//Wanhoop test
	// 	tmp = ft_strdup((*sort)->str);
	// 	free ((*sort)->str);
	// 	(*sort)->str = NULL;
	// 	(*sort)->str = check_path(*_env, tmp);
	// 	//							
	// 	if((*sort)->str == NULL)
	// 		return(ENOMEM);
	// 		//return(malloc_fail(ENOMEM));
	// 	if (!ft_strcmp(str_before, (*sort)->str))
	// 		builtin_type = builtin_no_com;
	// }
	
		// (*sort)->str = check_path(*_env, (*sort)->str);
		// (*sort)->str = delete_quotes((*sort)->str, (*sort)->str[0]);


// tmp = ft_strdup((*sort)->str);
		// free ((*sort)->str);
		// (*sort)->str = NULL;

----
		printf("VOOR:[%p] [%s]\n", (*sort)->str, (*sort)->str);
		printf("VOOR TMP:[%p] [%s]\n", tmp, tmp);
		printf("NA: [%p] [%s]\n", (*sort)->str, (*sort)->str);
		printf("TMP2:[%p] [%s]\n", tmp, tmp);
		printf("NA DQ: [%p] [%s]\n", (*sort)->str, (*sort)->str); 
		
		printf("FREE:[%p] [%s]\n", *str, *str);
		printf("TMP1:[%p] [%s]\n", tmp, tmp);  
----

/***********************
* count_node
************************/

** Changelog 08/09:
	- Count_node aangepast zodat we van ? af zijn in fill_builtin_redirec_array
	- Big changes in check_builtin_node: quotes veel korter (gaat dit goed?), check_path toevoeging.

/***********************
* trunc quotes											---> Gebruiken we volgens mij niet
************************/

/*
** Changelog:
	- Added 29/09(na vak):
	free(str);				//freet dit de (*sort)->str) goed?
*/

// char            *trunc_quotes(char *str)
// {
//     int     len;
//     char     *newstr;

//     len = ft_strlen(str);
//     len = len - 2;
// 	newstr = ft_substr(str, 1, len);
// 	free(str);
//     return (newstr);
// }

/***********************
return_type_and_free
************************/
/*
**	../ toevoeging bij executables beetjes spannend of dat goed is.
*/


/***********************
get_builtin_type
************************/

Verwijderd:
// else if (!ft_strncmp(tmp, "/", 1) || !ft_strncmp(tmp, "./", 2) ||
	// 			!ft_strncmp(tmp, "../", 3))

else if (ft_strchr(tmp, '/'))							//Voor echo/


/***********************
delete_quotes
************************/

/* Waarom hadden we eerst:
if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
	{
		newstr = trunc_quotes((*sort)->str);
		builtin_type = get_builtin_type(newstr);
		printf("(*sort)->str = [%s]\n", (*sort)->str);
		free (newstr);
		return (builtin_type);
	}
	--> Waarom niet direct sort->str ontdoen van quotes? Hier was vast een reden voor.
** TO DO:
	- We moeten nu 2x quotes truncen (general en hieronder). Kunnen we structuur aanpassen zodat dit maar 1x hoeft?
*/

/*
"\echo" hallo
bash: \echo: command not found

echohallo: command not found
"echo"hallo

*/

	// printf("Delete quotes src = [%p][%s] .  [%p]\n", src, src, &src);
	// printf("Delete quotes dst = [%p][%s] .  [%p]\n", dst, dst, &dst);
	// dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	// printf("Delete quotes dst = [%p][%s]\n", dst, dst);

		// printf("Delete quotes dst= [%p][%s] .  [%p]\n", dst, dst, &dst);

			printf("dst_i = %d\n", dst_i); 


	// printf("src len = %zu --> [%s]\n", ft_strlen(src), src); 
	// printf("dst_i = %d en len = %d\n", dst_i, len); 
	// printf("len - 2 = %d\n", len); 
		// printf("dst_i[%d] wordt  src[%d][%c]\n", dst_i, src_i, src[src_i]);
			// printf("dst_i[%d] = [%c]\n", dst_i, dst[dst_i]);  

--------
IN DELETE QUOTES ZAT EEN GROTE FOUT QUA LOOPEN, OPGELOST. ZIE VERSIE VOIR 31/10 voor oude.
-------
Na aanpassing:
dst[dst_i] = '\0'; 			//kan dit ipv len?





---------------------------------------------
ll_make_list_parser.c
---------------------------------------------

// new->quote = NULL;
new->builtin = builtin;		// was -1

---------------------------------------------
output.c
---------------------------------------------
str = ft_strdup((*sort)->str);			//gemallocte str en gemallocte sort->str // Wat gebeurt er met gemallocte sort>str

new->str_output = str_output;			//Gemalloct wordt deze gefreet?



---------------------------------------------
free_list.c
---------------------------------------------
/*
** TO DO:
    - Kennelijk hoeven we bij free_input en free_output str_.... niet te freeen. Waarom is dat?
    Is deze niet gemalloct?
    Ik zou verwachten dat we een gemallocte str doorkrijgen vanuit sort. Misschien omdat we deze al in lexer freeen dat het oke is?

** ANTWOORD:
    We hoefte idd niet te freeen omdat we de gemallocte str doorkregen vanuit sort. Consequentie na het freeen van lexer dat we deze gemallocte string dus wel kwijt waren.
    Oplossing: ft_strdup toegevoegd, lexer kan gefreet, str_input en str_output blijven wel bestaan, ze moeten nu ook gefreet worden. 
*/

/*
** TO DO:
    - Beslissen of we de inidividuele arrays binnen **array ook gaan mallocen (net als in split).
    ZO niet, niet freeen. Zo wel freeen! [SOLVED].
*/
		// printf("FREE array[y] = [%p][%s]\n", array[y], array[y]);

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


free_list_parser(t_command **command):
		// if ((*command)->quote)						
		// 	free((*command)->quote);			//new		//GEBRUIKEN WE DIE WEL OF NIET?

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


------------
SOPHIES FREE ARRAY:
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
		------------


----------------------------------------------------------------------------------------
EXECUTE
=========================================================================================

---------------
execute.c
---------------
/*
** TO DO:
	- //welke exit code? bij errno_error
	- if ((*command)->builtin == builtin_no_com)		//Twijfel of dit goed gaat. Toegevoegd vanwege $echo hallo
*/

/***************/
execute
/***************/
complete_path(command, *_env);		// maakt van echo/ no --> no_com

	if (g_own_exit != 999 && (*command)->builtin == builtin_no_com && (*command)->array)				//new		//(*command)->array voor pwd ; $POEP ; echo doei

	else			//reset g_own
			g_own_exit = 0;										//new
/*
29/10: verwijderd ivm pwd ; $POEP ; echo doei

			// if ((*command)->builtin == builtin_no_com && !((*command)->sem || (*command)->pipe_after) && (!(*command)->array || !(*command)->array[0]))		//M: Welke case komt dit voor? anders liever verwijderen. S: $POEP komt het voor
			// {																																				// Sem en pipe toegevoegd voor pwd ; $POEP ; echo doei
			// 	free(exe);
			// 	return (0);
			// }

*/

		if(res == 3) 													// 3 staast voor de return uit errno_error S: wel handig om dit voorbeeld nog even op te zoeken


Delete:
	// exe = (t_execute *)malloc(sizeof(t_execute));
	// if (!exe)
	// 	malloc_fail();
		// {
		// 	close_execute(&exe);
		// 	free(exe);
		// 	return(0);    // or own exit status op 0 zodat hij eruit klapt 
		// }
	// close_execute(&exe);
	// free(exe);
	// return (0);





/***************/
complete_path
/***************/

str_before = ft_strdup((*command)->array[0]);					//alleen 0?

/*
** MOE:
		g_own_exit = 0;				//Welke de g_own?

	// if (((*command)->builtin == builtin_no_com && 
		// 		(!(*command)->array || !(*command)->array[0]) &&
		// 			 (!(*command)->pipe_after && !(*command)->sem)) ||  g_own_exit != 0)		//uitgecomment

LAATSTE VERSIE VOOR fixes 23/10 : ga dan terug naar ---> 23/10 fixed capital commands, removed MOE
		// printf("array[0] = [%p][%s] -> &[%p]\n", (*command)->array[0], (*command)->array[0], &(*command)->array[0]);
*/


/***************/
Builtin_another_program
/***************/
/*
** MOE:
	if ((*command)->array && (*command)->array[0])
*/


/***************/
invoke_another_program
/***************/
	signal(SIGINT, signal_reset);							//new vw signals
	errno_error((*command)->array[0], *command);								// --> 1 van de foutmeldingen van unset PATH ; ls
	if (WIFSIGNALED(status)) 							///NEW vw signals




---------------
get_path.c
---------------
/***************/
check_path
/***************/
path = search_node(_env, ft_strdup("PATH"));	//vanwege free in search node

	if (!path)
		return (str);			// was return (errno = ENOENT, errno_error(str));

		if (ft_strcmp(next_entry->d_name, tmp) == 0) //was str
			str = make_path_complete(patharray[i], tmp); //was str

/* Removed:
	///	
	// if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	// 	return (error_command(str));
	// else 
*/

/*
** MOE:
	///	
	// if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	// 	return (error_command(str));
	// else 
*/

---------------
execute_utils.c
---------------
X

---------------
check_specials.c
---------------
/*
** TO DO:
	- Single quotes: //Freeen oude malloc?
	!!! - Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).	
*/
if (is_single_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;

if (is_double_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;


Save:
// check_if_quotes(command, &flag, y, &i, _env);
--> 
// static void		check_if_quotes(t_command **command, int *flag, int y, int *i, t_env *_env)
// {
// 	char	*tmp;

// 	if (is_single_quote((*command)->array[y][*i]) && !(*flag))
// 	{
// 		tmp = strdup_and_free(&(*command)->array[y]);
// 		(*command)->array[y] = treat_single_quote(tmp, i, flag);
// 	}
// 	if (is_double_quote((*command)->array[y][*i]) && !(*flag))
// 	{
// 		tmp = strdup_and_free(&(*command)->array[y]);
// 		(*command)->array[y] = treat_double_quote(tmp, i, _env, flag);
// 	}
// 	// printf("str =  [%s]\n", *str);
// 	return ;
// }


--------

if ((*command)->array[y][*i] == '\\')
	{
		// tmp = ft_strdup((*command)->array[y]);
		// free((*command)->array[y]);
		// (*command)->array[y] = NULL;

if ((*command)->array[y][*i] == '$' &&
			(*command)->array[y][*i + 1] == '\\')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;

			if ((*command)->array[y][*i] == '$')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;


		// printf("BEFORE: [%p][%s]\n", (*command)->array[y], (*command)->array[y]);
		// printf("AFTER:  [%p][%s] --> tmp [%s]\n", (*command)->array[y], (*command)->array[y], tmp);


---------------
treat_double_quote
---------------
	tmp = ft_strdup(str);
	free(str);
	str = check_backslash_and_dollar(tmp, i, _env);

	tmp = ft_strdup(str);
	free(str);
	str = delete_double_quotes(tmp, start, end);

	if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);

---------------
treat_double_quote
---------------
end = *i;
	tmp = ft_strdup(str);
	free(str);
	str = delete_quotes(tmp, '\'');


if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_substr(tmp, 1, ft_strlen(tmp));


---------------
if_no_quote
---------------
/*
** Check_builtin_again: checks if there are commands in the _env variables ($)
** Ex. export LS="ls -la" 
*/





---------------
GET PATH.c
---------------

char			*check_path(t_env *_env, char *str)
{
	struct dirent 	*next_entry;
	DIR				*folder;
	char			*path;
	char 			**patharray;
	int				i;
	char 			*tmp;

	i = 0;
	path = search_node(_env, ft_strdup("PATH"));
	if (!path)
		return (str);
	patharray = ft_split(path, ':');
	if (!patharray)
		return (NULL);
	tmp = tmp_tolower(str);
	while (patharray && patharray[i])
	{
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			while ((next_entry = readdir(folder)) != NULL)
			{
				if (ft_strcmp(next_entry->d_name, tmp) == 0)
				{
					free(str);
					str = NULL;
					str = make_path_complete(patharray[i], tmp);
					closedir(folder);
					free_array(patharray);
					free(path);
					return (str);
				}
			}
			closedir(folder);
		}
		i++;
	}
	free(tmp);
	free_array(patharray);
	free(path);
	return (str);
}

	if (!patharray)
		return (NULL); 								//Gaat dit goed? path returnde old str
		

error_command((*command)->array[0], 1, *command);			//NOG EVEN CHECKEN OF NULL GOED GAAT
