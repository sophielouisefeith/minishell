/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/10/16 18:11:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** TO DO:
	- Proberen of "while ((*command)->array && (*command)->array[y])" combi ook bij parser werkt, ipv if next bestaat.
	- echo $USER\			--> Merel laat \ weg en print de rest
	- echo $USER|			--> Merel doet niks, gewoon nieuwe prompt
	- Moeten we dit nog verplaatsen naar lexer/parser?
	- Testen: Export expand hij ook name en value
	- Functies te lang.
*/

/*
** When the given parameter (ex. $POEP) doesn't exist in _env:
** check if there a more parameters coming, if so delete the non_existing one
** and move the others in the array. If there are no other parameters,
** the non_existing one will be deleted and the whole 2D array also.
** TO DO:
	- LET OP BIJ FREEEN, gaat dit dan goed?
*/

void		parameter_not_exist(t_command **command, int *y)
{
	int		new_y;

	if (!(*command)->array[*y + 1] && !(*command)->array[*y - 1])
	{
		free((*command)->array[*y]);
		free((*command)->array);
		(*command)->array[*y] = NULL;
		(*command)->array = NULL;
	}
	else
	{
		new_y = *y - 1;
		while ((*command)->array[*y + 1])
		{
			(*command)->array[*y] = (*command)->array[*y + 1];
			(*y)++;
		}
		(*command)->array[*y] = NULL;
		(*y) = new_y;
	}
///
	// int n = 0;
	// while ((*command)->array[n])
	// 	{
	// 		printf("Not exist print: [%d][%s]\n", n, (*command)->array[n]);
	// 		n++;
	// 	}
///	
}

/*
** parameter --> $parameter
** new_str1	-->	 string before $parameter
** new_str2 -->  string after $parameter
**
** 1. i > 0 means the $ sign is not on the first element of the string.
** Therefore everything before $ should be saved in a string.
** 2. Check if there are more special characters after $
** (not alphanumeric and printable, except '_'). Because special chars would
** mean a new string, aphanummeric or '_' would be considered part of the
** $parameter.
** Also check for immediate end of line after $.
** 3. ret == -1 --> Immediate end of line meaning that $ sign should be printed
**    ret == 0  --> no special chars found, so no string after the $parameter 
**    ret > 0   --> special char found, so new_str after $parameter, save in 
**		new_str2. Ret is position of special char.
// ** 4. If there is a new_str2 (ret > 0) check if special char is a $. If so this		//wat als nog $? erachter
// ** one should be expanded as wel (recursive).
** 5. If not immediate end of line, search for parameter in _env.
** 6. Join the 3 possible strings, and return this new value.
*/

//cijfers mogen in _env naam alleen niet op de eerste plaats!
//DUs als op eerste plaats ret > 0




/*
** ** Exceptions:
** Quote: $" $' $\ return the whole string (ex. )
** 			if (ret > 0 && str[ret - 1] == '$' && (str[ret] == '\"' || str[ret] == '\'' || str[ret] == '\\'))	
	//Quote exception + $\ exception(only for quotes)
	/$"poep" returnt de hele string min de $
**
*/



char			*if_dollar(char *str, int *i, t_env *_env)
{
	char	*new_str1;
	char	*new_str2;
	char	*parameter;
	int		ret;

	int flag_qm;
	int flag_group2;
	flag_qm = 0;
	flag_group2 = 0;

	new_str1 = NULL;
	parameter = NULL;
	new_str2 = NULL;
	if (*i > 0)
		new_str1 = ft_substr(str, 0, *i);
	ret = expand_is_special_char(str, (*i + 1));
	if (ret == -1)
		parameter = "$";
	if (ret == 0)
		parameter = ft_substr(str, (*i + 1), ft_strlen(str));
	if (ret > 0 && str[ret - 1] == '$' &&
		(str[ret] == '\"' || str[ret] == '\'' || str[ret] == '\\'))			//GROEP 0: Verwijder enkel $ en i--. // meer testen! echo /$"123$USER" of echo $\abc // SNAP NIET DTA WERKT
			new_str2 = ft_substr(str, ret, ft_strlen(str));			//volgens mijn substringen we niet de goede len!!!! ft_strlen - ret.
	if (ret > 0)
	{
		if (str[ret - 1] == '$')
		{
			if ((str [ret] >= '0' && str[ret] <= '9') || str[ret] == '*'
				|| str[ret] == '@' || str[ret] == '!' || str[ret] == '&'
				|| str[ret] == '$' || str[ret] == '#'
				|| str[ret] == '-')																//Groep 1 (en 3 specials): verwijder $ + eerste teken
				new_str2 = ft_substr(str, (ret + 1), ft_strlen(str)); //malloc freet niet
			if (str[ret] == '%' || str[ret] == '^' || str[ret] == '+' || str[ret] == ',' ||		//Groep 2: print alles
				str[ret] == '.' || str[ret] == '/' || str[ret] == ':' || str[ret] == '=' || 
				str[ret] == ']' || str[ret] == '}' || str[ret] == '~')//str[ret] == '\"' || str[ret] == '\'' || str[ret] == '\\')		//laatste 3 experiment
				{
					flag_group2 = 1; //mag niet i--
					new_str2 = ft_substr(str, *i, ft_strlen(str));
				}
			if (str[ret] == '?')																//Groep 4: vervang $? voor exitstatus
			{
				flag_qm = 1;
				parameter = ft_itoa(g_exit_status);
				new_str2 = ft_substr(str, (ret + 1), ft_strlen(str));
			}
		}
		else
		{
			parameter = ft_substr(str, (*i + 1), (ret - *i - 1));
			new_str2 = ft_substr(str, ret, ft_strlen(str));
		}
	}
	if (ret != -1 && parameter && !flag_qm)
		parameter = search_node(_env, parameter);
	if (new_str2 && !flag_group2 && (new_str2[0] == '$' || new_str2[0] == '\'' || new_str2[0] == '\"')) //vw bijv echo $2$* of echo $hallo"poep"
		(*i)--;
	// printf("newstr1: %s\n", new_str1);
	// printf("parameter: %s\n", parameter);
	// printf("new_str2= %s\n",new_str2);
	parameter = join_strings(new_str1, parameter, new_str2);
	return (parameter);
}

//TO DO: backslash wel naar kijken

	// printf("ret[%d]= %c\n", ret, str[ret]);
				// printf("newstr2: %s\n", new_str2);
	// printf("ret = %d\n", ret);
	// printf("return = %s\n", parameter);
	// printf("parameter: %s\n", parameter);

/*
** In bash there are multiple functions/special variables/event we don't have to treat. For example:
** echo $! --> process ID (PID), !!, !<anything behind it>
** & --> run in the background, && --> AND, run left and right in sequence.
** echo $$ --> process ID (PID)
** #, echo #, echo $# --> number of arguments
** echo $- --> prints the current set of options in your current shell.
** echo *	--> wildcard
** We don't handle those cases, meaning also no error. To present an error we should know
** all the cases we shouldn't treat. We only treat what the subject tells us to treat.
**/

/*
			if ((str[ret] == '!' || str[ret] == '&' || str[ret] == '$' || str[ret] == '\\' ||	//Groep 3: specials, geen onderdeel van subject // (str[ret] == '!' && str[ret + 1]) 
				str[ret] == '#' || str[ret] == '-')
			{
				error_parameter(ft_substr(str, ret - 1, 2));
				(*i)++;
				return (str);	
			}

			// if (str[ret] == '\\')		//alleen als buiten haakjes
			// {
			// 	flag = 1;
			// 	parameter = "$";
			// 	new_str2 = ft_substr(str, (ret + 1), ft_strlen(str));
			// }
*/


/*
Removed " en ' exception:
	// parameter = "$";
		// new_str2 = ft_substr(str, ret, ft_strlen(str));
		// printf("new_str2 = %s\n", new_str2);
		// ret = -1;


*/









// echo $USER_			segt na tijdje

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Single quote cases will not be expanded.
** Break out of first while loop when handled $. Optional other $ in
** the array[y] are already handled.
*/

// char		*if_dollar(char *str, int i, t_env *_env)
// {
// 	char	*value;

// 	value = expand(str, i, _env);
// 	return (value);
// }
