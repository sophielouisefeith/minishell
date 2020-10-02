/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/10/02 16:47:14 by maran         ########   odam.nl         */
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

char			*expand(char *str, int i, t_env *_env)
{
	char	*new_str1;
	char	*new_str2;
	char	*parameter;
	int		ret;

	new_str1 = NULL;
	parameter = NULL;
	new_str2 = NULL;
	if (i > 0)
		new_str1 = ft_substr(str, 0, i);
	ret = is_special_char(str, (i + 1));
	if (ret == -1)
		parameter = "$";
	if (ret == 0)
		parameter = ft_substr(str, (i + 1), ft_strlen(str));
	if (ret > 0 && str[ret - 1] == '$' && str[ret] == '\"')		//new execption (nu wel te lang)
	{
		parameter = "$";
		new_str2 = ft_substr(str, ret, ft_strlen(str));
		ret = -1;
	}
	if (ret > 0)
	{
		parameter = ft_substr(str, (i + 1), (ret - i - 1));
		new_str2 = ft_substr(str, ret, ft_strlen(str));
	}
	if (ret != -1)
		parameter = search_node(_env, parameter);
	parameter = join_strings(new_str1, parameter, new_str2);
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

	if (str[i + 1] == '?')
		value = ft_itoa(g_exit_status);
	else
		value = expand(str, i, _env);
	return (value);
}
