/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/10/19 16:55:31 by maran         ########   odam.nl         */
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
	- Volgens mijn substringen we niet de goede len (ft_strlen - ret)
*/

/*
** When the given parameter (ex. $POEP) doesn't exist in _env:
** check if there a more parameters coming, if so delete the non_existing one
** and move the others in the array. If there are no other parameters,
** the non_existing one will be deleted and the whole 2D array also.
*/

static int		check_for_other_parameters(char **array, int y)
{
	if (y > 0)
	{
		if (!array[y + 1] && !array[y - 1])
			return (1);
	}
	else
	{
		if (!array[y + 1])
			return (1);
	}
	return (0);
}

void			parameter_not_exist(t_command **command, int *y)
{
	int			new_y;
	
	if (check_for_other_parameters((*command)->array, *y))
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
** Group 0 - 4: immediately behind $ is a special char
** 	-Group 0: $ stays, remove first special char
**	-Group 1 and 3: remove $ and first special char
**	---------------------------------------------------------------------------
** 	Group 3 are special variables with a function in the real bash. These don't
**  have to be handled in this project. We treat them as group1 characters.
** 	For example:
** 	echo $!, !!, !<anything behind it>, &, &&, echo $$, #, echo #, echo $#,
**  echo $-, echo *
** 	We don't handle those cases, meaning also no error. To present an error we
** 	should know all the cases we shouldn't treat. We only treat what the subject
** 	tells us to treat.
**	---------------------------------------------------------------------------
**	-Group 2: $ and first special char stay
** 	($?) Expands to the exit status of the most recently executed foreground
** 	pipeline.
** Group 5: No special char immediately behind $.
**	$ stays, remove first special char
*/

static int		group_and_start_newstr2(char *str, char ret, int i, int *start)
{
	int			group;

	if (str[ret - 1] == '$')
	{
		if (str[ret] == '\"' || str[ret] == '\'' || str[ret] == '\\')
			group = 0;
		if ((str [ret] >= '0' && str[ret] <= '9') || str[ret] == '*'
			|| str[ret] == '@' || str[ret] == '!' || str[ret] == '&'
			|| str[ret] == '$' || str[ret] == '#'
			|| str[ret] == '-')
			group = 1;
		if (str[ret] == '%' || str[ret] == '^' || str[ret] == '+' ||
			str[ret] == ',' || str[ret] == '.' || str[ret] == '/' ||
			str[ret] == ':' || str[ret] == '=' || str[ret] == ']' ||
			str[ret] == '}' || str[ret] == '~')
			group = 2;
		if (str[ret] == '?')
			group = 4;
	}
	else
		group = 5;
	*start = (group == 1 || group == 4) ? (ret + 1) : ret;
	*start = (group == 2) ? i : (*start);												
	return (group);
}	

static void		special_char_found(t_dollar **dollar, char *str, int i)
{
	int 		group;
	int 		start;

	group = group_and_start_newstr2(str, (*dollar)->ret, i, &start);
	if (group == 0 && (*dollar)->quote)
	{
			(*dollar)->flag_group2 = 1;
			(*dollar)->ret = -1;
			(*dollar)->parameter = ft_strdup("$");
	}
	if (group == 2)
		(*dollar)->flag_group2 = 1;
	if (group == 4)
	{
		(*dollar)->flag_qm = 1;
		(*dollar)->parameter = ft_itoa(g_exit_status);
	}
	if (group == 5)
		(*dollar)->parameter = ft_substr(str, (i + 1),
			((*dollar)->ret - i - 1));
	(*dollar)->new_str2 = ft_substr(str, start, ft_strlen(str));
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
** 4. If there is a new_str2 (ret > 0) check if special char is a exception
** character (see groups).
** 5. If not immediate end of line, search for parameter in _env. Except for $?
** this is a special which shows the exit_status.  
** 6. Join the 3 possible strings, and return this new value.
*/

char			*if_dollar(char *str, int *i, t_env *_env, int quote)
{
	t_dollar	*dollar;

	dollar = (t_dollar *)malloc(sizeof(t_dollar));
	initiate_dollar(dollar, quote);
	if (*i > 0)
		dollar->new_str1 = ft_substr(str, 0, *i);
	dollar->ret = dollar_is_special_char(str, (*i + 1));
	if (dollar->ret == -1)
		dollar->parameter = ft_strdup("$");
	if (dollar->ret == 0)
		dollar->parameter = ft_substr(str, (*i + 1), ft_strlen(str));
	if (dollar->ret > 0)
		special_char_found(&dollar, str, *i);
	if (dollar->ret != -1 && dollar->parameter && !dollar->flag_qm)
		dollar->parameter = search_node(_env, dollar->parameter);
	if (dollar->new_str2 && !dollar->flag_group2 && (dollar->new_str2[0] == '$'
		|| dollar->new_str2[0] == '\'' || dollar->new_str2[0] == '\"'))
		(*i)--;
	dollar->parameter = join_strings(dollar->new_str1, dollar->parameter,
		dollar->new_str2);
	return (dollar->parameter);
}
