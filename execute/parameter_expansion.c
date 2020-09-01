/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/09/01 18:14:49 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Single quote cases will not be expanded.
** TO DO:
	- strtrim trimt van 2 kanten gaat dat wel goed?
	- Moeten we ook braces?
	- Export expand hij ook name en value
*/

static char		*search_node(t_env *_env, char *search)
{
	while (_env)
	{
		if (!ft_strcmp(search, _env->name))
			return (_env->value);
		_env = _env->next;
	}
	return (NULL);
}

/*
** When the given parameter (ex. $POEP) doesn't exist in _env:
** check if there a more parameters coming, if so delete the non_existing one
** and move the others in the array. If there are no other parameters,
** the non_existing one will be deleted and the whole 2D array also.
** TO DO:
	LET OP BIJ FREEEN, gaat dit dan goed?
*/

static void		parameter_not_exist(t_command **command, int *y)
{
	int		new_y;

	if (!(*command)->array[*y + 1])
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
** TO DO:
	- Proberen of "while ((*command)->array && (*command)->array[y])" combi ook bij parser werkt, ipv if next bestaat.
*/

/*
strlcat() appends string src to the end of dst

echo --$USER--
--msiemons--



Voor $:
Letters OK
Cijfers OK
Speciale tekens OK

Na $USER:
Letters NIET OK
Cijfers NIET OK
Speciale tekens OK
 
 Wat als nog een $USER
 */

// Wat wel en wat niet?:
// ! is ook nog iets speciaals // dit hoeft waarschijnlijk niet.
// hallo$USER&
// & ook iets speciaals
// En nog veel meer specials :(

/*
" not complete
( ! & gewoon printen
echo $USER\				--> Merel laat \ weg en print gewoon
echo $USER_				--> underscore wordt gezien als een alpha
ascii 96 ook gewoon printen
echo $USER|				-->doet niks gewoon nieuw prompt

 */
 
/*
** HADDEN WE NIET OOK MOETEN SPLITTEN OP $ in lexer?					!!!
*/
static int			is_special_char(char *str, int i)
{
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;

	}
	return (0);
}


/*
	new_str1	value		new_str2
	0			0			0
	1			1			1
	1			0			0
	1			1			0
	1			0			1
	0			1			0
	0			1			1
	0			0			1
 */
static char			*join_strings(char *new_str1, char *value, char *new_str2)
{
	char *joined;

	if (!new_str1 && !value && !new_str2)
		return (NULL);
	if (new_str1 && value && new_str2)
	{
		joined = ft_strjoin(new_str1, value);
		joined = ft_strjoin(joined, new_str2);
	}
	if (new_str1 && !value && !new_str2)
		joined = new_str1;
	if (new_str1 && value && !new_str2)
		joined = ft_strjoin(new_str1, value);
	if (new_str1 && !value && new_str2)
		joined = ft_strjoin(new_str1, new_str2);
	if (!new_str1 && value && !new_str2)
		joined = value;
	if (!new_str1 && value && new_str2)
		joined = ft_strjoin(value, new_str2);
	if (!new_str1 && !value && new_str2)
		joined = new_str2;
	// printf("joined = [%s]", joined);
	return (joined);
}

//echo $USER	$USER
//     01234	56789


// CHECK OF IETS NA $, zo niet gewoon printem 

static char			*expand(char *str, int i, t_env *_env)
{
	char	*new_str1;
	char	*env_str;
	char	*new_str2;
	char	*value;
	int		len;
	int		ret;

	new_str1 = NULL;
	env_str = NULL;
	new_str2 = NULL;
	len = ft_strlen(str);
	if (i > 0)
	{ 
		new_str1 = ft_substr(str, 0, i);							//Substr alles voor $, mits er iets voor staat
			
	}
	ret = is_special_char(str, (i + 1));							//scan of rest van string nog speciale karakters heeft
	if (ret > 0)
	{
		env_str = ft_substr(str, (i + 1), (ret - i - 1)) ;
		new_str2 = ft_substr(str, ret, len);					//Substr alles vanaf special char 		//to do:check of dit weer nieuwe expansion is
		if (new_str2[0] == '$')
			new_str2 = expand(new_str2, 0, _env);
	}
	if (ret == 0)
	{
	// 	if (str[1] == '\0')			//mehhhh
	// 		env_str = "$";
	// 	else
			env_str = ft_substr(str, (i + 1), len);					//i + 1 zodat $ eraf
		
	}
	value = search_node(_env, env_str);
	printf("[%s][%s][%s]\n", new_str1, env_str, new_str2);
	value = join_strings(new_str1, value, new_str2);
	return (value);
}


// static char			*expand(char *str, int i, t_env *_env)
// {
// 	char	*new_str1;
// 	char	*env_str;
// 	char	*new_str2;
// 	char	*value;
// 	int		len;
// 	int		ret;

// 	new_str1 = NULL;
// 	env_str = NULL;
// 	new_str2 = NULL;
// 	len = ft_strlen(str);
// 	if (i > 0)
// 		new_str1 = ft_substr(str, 0, i);							//Substr alles voor $, mits er iets voor staat
// 	ret = is_special_char(str, (i + 1));							//scan of rest van string nog speciale karakters heeft
// 	printf("ret = %d\n", ret);
// 	if (ret > 0)
// 	{
// 		printf("ret = %d\n", ret);
// 		env_str = ft_substr(str, (i + 1), (ret - i - 1)) ;
// 		printf("env_str = [%s]\n", env_str);
// 		new_str2 = ft_substr(str, ret, len);					//Substr alles vanaf special char 		//to do:check of dit weer nieuwe expansion is
// 		printf("new_str2= [%s]\n", new_str2);
// 	}
// 	if (ret == 0)
// 		env_str = ft_substr(str, (i + 1), len);					//i + 1 zodat $ eraf
// 	value = search_node(_env, env_str);
// 	// if (value == NULL)
// 	// printf("[%s][%s][%s]\n", new_str1, env_str, new_str2);
// 	value = join_strings(new_str1, value, new_str2);
// 	// printf("value[%s]\n", value);
// 	return (value);
// }

 
void			parameter_expansion(t_command **command, t_env *_env)
{
	char	*value;
	int		y;
	int		i;
	int		len;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while((*command)->array[y][i])
		{
			if ((*command)->array[y][i] == '$' && (*command)->quote[y] != token_quote)
			{
				if (!ft_strcmp("$?", (*command)->array[y]))
					value = ft_itoa((*command)->exit_status);
				else
					value = expand((*command)->array[y], i, _env);
				if (value == NULL)
					parameter_not_exist(command, &y);
				else
					(*command)->array[y] = value;
				break ;								//moet uit eerste while loop
			}
			i++;
		}
		y++;
	}	
	
}
