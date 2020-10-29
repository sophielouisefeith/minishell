/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion_sop.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 12:28:00 by SophieLouis   ########   odam.nl         */
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

static char 	*check_for_more_expansion(char *new_str2, t_env *_env)
{
	int		i;

	i = 0;
	while (new_str2[i])
	{
		if (new_str2[i] == '$')
			new_str2 = expand(new_str2, i, _env);
		i++;
	}
	return (new_str2);
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

	// printf("str[%d] = [%c]\n", ret, str[ret]);
	// printf("new_str1 = [%s]\n", new_str1); 
		// printf("NO special char: parameter = [%s]\n", parameter); 
		// printf("Special char found: parameter = [%s]\n", parameter); 
		// printf("Special char found: new_str2 = [%s]\n", new_str2);
	// printf("Return = [%s]\n", parameter);


static char			*exception(char *str, int ret, char *parameter)
{
	int count;
	char *new_str1;
	char *new_str2;
	count = 0;
	// printf("exeption\n");
	// printf("-------------parameter[%s]\n", parameter);
	// printf("-------------str[%s]\n", str);
	// printf("ret[%d]\n", ret);
	// if(parameter)
	// {
	// 	printf("str[%c]\n", str[count]);
	// 	while(str[count]!= '$' && str[count] != '\0')
	// 		count ++;
	// 	new_str1 = ft_substr(str, 0, count);
	// 	new_str2 = ft_substr(str, ret, ft_strlen(str));
	// 	printf("-------------new_str[%s]\n", parameter);
	// 	parameter = join_strings(new_str1, parameter, new_str2);
	// 	printf("-------------pr[%s]\n", parameter);
	// 	return(parameter);
	// }
	if(str[ret] == '^')
		return(str);
	else if(str[ret] == '#')
	{
		str[ret] = '0';
		parameter = ft_substr(str, 1, ft_strlen(str));
		return(parameter);
	}
	else if(str[ret] == '@')
	{
		parameter = ft_substr(str, 2, ft_strlen(str));
		return(parameter);
	}
	else
		return(not_part(str));
	return(parameter);
}

char			*expand(char *str, int i, t_env *_env)
{
	//printf("expand\n");
	char	*new_str1;
	char	*new_str2;
	char	*parameter;
	int		ret;
	int 	except;

	new_str1 = NULL;
	parameter = NULL;
	new_str2 = NULL;
	if (i > 0)
	{
		new_str1 = ft_substr(str, 0, i);
		//printf("new_str1[%s]\n", new_str1);
	}
	ret = is_special_char(str, (i + 1));
	if (ret == -1)
	{
		//printf("-------------ret == -1[%d]\n", ret);
		// if(str[i+1] == '>')
		// 	printf("bash: syntax error near unexpected token `>'\n");
		parameter = "$";
		if(new_str2 == NULL) //&& ft_strcmp(parameter ,“$”						//Is toch altijd NULL hier
        {
            parameter = join_strings(new_str1, parameter, new_str2);
            // printf(“parameter for extra [%s]\n”, parameter);
            return(parameter);
        }
	}
	if (ret == 0)
	{
		//printf("-------------ret == 0[%d]\n", ret);
		parameter = ft_substr(str, (i + 1), ft_strlen(str));
	}
	// if((ret > 0 && str[ret - 1] == '$' && str[ret] == '\"') \				// if((ret > 0 && str[ret - 1] == '$' && (str[ret] == '\"') || str[ret] == '\'' ))	
		// || (ret > 0 && str[ret - 1] == '$' && str[ret] == '\'' ))	
	if(ret > 0 && str[ret - 1] == '$' && (str[ret] == '\"' || str[ret] == '\''))
	{
		//printf("qoutes\n");
		parameter = "$";
		new_str2 = ft_substr(str, 0, ft_strlen(str));
		// printf("parameter[%s]\n", parameter);
		// printf("new_str1[%s]\n", new_str1);
		// printf("new_str2[%s]\n", new_str2);
		parameter = join_strings(new_str1, parameter, new_str2);		//ik zette ret op -1 zodat hij niet nog in andere if checks ging. En wel parameter join str
		
		// return(new_str2);												
		return(parameter);
		// ret = -1;
	}
	if (ret > 0)												//VANAF HIER NIEUW
	{
		// printf("-------------ret > 0[%d]\n", ret);
		// printf("str[%s]\n", str);
		// printf("str[%c]\n", str[ret]);
		parameter = ft_substr(str, (i + 1), (ret - i - 1)) ;
		new_str2 = ft_substr(str, ret, ft_strlen(str));
		new_str2 = check_for_more_expansion(new_str2, _env);			// recursive check is terug? Maar hij komt toch sowieso weer terug hier via check_specials?
		except = 1;
		if(str[ret] == '%')
			return(str);
		//if(str[ret] == '\"' && )
		parameter = ft_substr(str, (i + 1), (ret - i - 1));				//?
		new_str2 = ft_substr(str, ret, ft_strlen(str));
		if(new_str2[0] == '\\')
			printf("backje\n"); 
	}
	if (ret != -1)
	{

		parameter = search_node(_env, parameter);
		parameter = join_strings(new_str1, parameter, new_str2);
		if(str[ret] == '^')
			return(str);
		if(str[ret] == '#')
		{
			if(str[ret-1] != '#' && str[ret -1] != '$')
			{
				parameter = ft_substr(str, ret, ft_strlen(str));
				return(parameter);
			}
			else
				str[ret] = '0';
				parameter = ft_substr(str, 1, ft_strlen(str));
			return(parameter);
		}
		if(str[ret] == '@' ||( str[ret] == '*' && str[ret +1] != '*') || (str[ret] == '!' && str[ret +1] != '!'))
		{
			parameter = ft_substr(str, 2, ft_strlen(str));
			return(parameter);
		}
		if((ft_isalpha(str[ret +1]) && !parameter)||\
		(str[ret] == '\"' && ft_isalpha(str[ret +1]) && !parameter))
			return(join_strings(new_str1, 0, new_str2));
		
		// printf("-------------ret != -1[%d]\n", ret);
		// parameter = search_node(_env, parameter);
		// printf("parameter[%s]\n", parameter);
		// printf("str[%c]", str[ret]);
		
		// else if(parameter && str[ret] =='$')
		// 	return(parameter);
		// 	//printf("alleen env\n");
		// else if(except)
		// 	return(exception(str, ret, parameter));
	}
	// printf("je bent gewoon cijfers\n");
	// if(ret == 5)
	// 	printf("je bent twee keer een dollar\n");
	// printf("parameter[%s]\n", parameter);
	// printf("new_str1[%s]\n", new_str1);
	// printf("new_str2[%s]\n", new_str2);
	//parameter = search_node(_env, parameter);
	if(new_str2 == NULL)
		parameter = join_strings(new_str1, parameter, new_str2);
	else
	{
		not_part(str);
		//printf("not part of the subject");
	}
	
	return (parameter);
}

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Single quote cases will not be expanded.
** Break out of first while loop when handled $. Optional other $ in
** the array[y] are already handled.
*/

char		*if_dollar(char *str, int i, t_env *_env)
{
	char	*value;
	// char	*number;			//niet gebruikt
	int		back;

	// number = &str[i +1];		//niet gebruikt
	if (str[i + 1] == '?')
	{
		value = ft_itoa(g_exit_status);
		i = 2;						//is i altijd 2?
		// if(str[i] == '?')		//moet het niet zijn als if(str[i])
		if (str[i])
		{
			str = ft_substr(str, 2, ft_strlen(str));
			return(value = ft_strjoin(value, str));
		}
	}
	else if(str [i + 1] >= '0' && str [i + 1] <= '9' && str[i + 1] != '?' ) //? zit toch niet tussen  0 en 9
		value = ft_substr(str, 2, ft_strlen(str));
	else
		value = expand(str, i, _env);
	return (value);
}


//**
//TESTS:
//hallo$?poep			werkt niet






			// printf("str[%s]\n", str);
// 

//en echo $A*aap  ook. Dus het is echt alle tekst na onbestaande $ of niet geldige $


// if(str[i] == '\\')
	// {
	// 	printf("back in dollar\n");
	// 	back = 1;
	// 	while(str[i] == '\\')
	// 	{
	// 		str = delete_escape_char(str, i);
	// 		printf("--------strhir[%s]\n", str);
	// 		//printf("--------backslash[%s]\n", parameter);
	// 		i++;
	// 		return(str);
	// 	}
			
	// }
	// else if( str [i + 1] >= '0' && str [i + 1] <= '9')
	// 	value = ft_substr(str, 2, ft_strlen(str));


// 	char			*expand(char *str, int i, t_env *_env)
// {
// 	char	*new_str1;
// 	char	*new_str2;
// 	char	*parameter;
// 	int		ret;
// 	int 	except;

// 	new_str1 = NULL;
// 	parameter = NULL;
// 	new_str2 = NULL;
// 	if (i > 0)
// 		new_str1 = ft_substr(str, 0, i);
// 	ret = is_special_char(str, (i + 1));
// 	if (ret == -1)
// 	{
// 		if(str[i+1] == '>')
// 			printf("bash: syntax error near unexpected token `>'\n");
// 		parameter = "$";
// 	}
// 	if (ret == 0)
// 		parameter = ft_substr(str, (i + 1), ft_strlen(str));
// 	if (ret > 0 && str[ret - 1] == '$' && str[ret] == '\"')		
// 	{
// 		parameter = "$";
// 		new_str2 = ft_substr(str, ret, ft_strlen(str));
// 		ret = -1;
// 	}
// 	if (ret > 0)
// 	{
// 		except = 1;
// 		if(str[ret] == '%')
// 			return(str);
// 		parameter = ft_substr(str, (i + 1), (ret - i - 1));
// 		new_str2 = ft_substr(str, ret, ft_strlen(str));
// 		if(new_str2[0] == '\\')
// 			printf("backje\n");   //dit wel of niet behandelen
// 	}
// 	if (ret != -1)
// 	{
// 		parameter = search_node(_env, parameter);
// 		if(ft_isalpha(str[ret +1]))
// 		{
// 			// parameter = search_node(_env, parameter);
// 			parameter = join_strings(new_str1, parameter, new_str2);
// 			return (parameter);
// 		}
// 		//else
// 		if(except)
// 		{
// 			//parameter = search_node(_env, parameter);
// 			return(exception(str, ret, parameter));
// 		}
// 	}
// 	parameter = join_strings(new_str1, parameter, new_str2);
// 	return (parameter);
// }