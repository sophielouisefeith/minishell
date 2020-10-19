/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/19 12:31:13 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*delete_escape_char(char *src, int n)
{
	char *dst;
	int dst_i;
	int src_i;
	int len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 1;
	dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	while (src[src_i] != '\0')
	{
		if (src_i == n)
			src_i++;
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	// printf("dst[%s]\n", dst);
	return (dst);
}


static char		*delete_double_quotes(char *src, int start, int end)
{
	char *dst;
	int dst_i;
	int src_i;
	int len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 2;
	dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	while (src[src_i] != '\0')
	{
		if (src_i == start || src_i == end)
		{
			src_i++;
			if (src_i == end)
				src_i++;
		}
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	return (dst);
}

/*
** Moet buitenste quotes op een andere manier verwijderen dan voorheen, omdat er ook quotes in het midden kunnen staan
Nadat echo "hallo\"\poep" --> \ wordt verwijderd, maar \poep wordt nog wel geprint alsof het binnen haakjes staat.
** Kijken of andere methode ook naar start end methode kan.
*/

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
**	- Escape character stills work in case of $ and \": 
**		* $: Operation of $ is gone and \ will be deleted.
**		* \":  the \ will be deleted. And " doesn't count as "has to be complete"
**		* Other: the \ will not be deleted.
** 	- Inner single quotes are considered as text, don't have to be complete.
*/



	// printf("In DQ: [%s]\n", str);
	// printf("start = (%d) = [%c]\n", *i, str[(*i)]);
		// printf("str[(%d)] = [%c]\n", *i, str[(*i)]);
	// printf("end = (%d) = [%c]\n", *i, str[(*i)]);
	// printf("Uit DQ: [%p][%s]\n", str, str);

static char			*treat_double_quote(char *str, int *i, t_env *_env, int *flag)
{
	int start;
	int end;
	int  dollar;
	// char *new_str;

	start = *i;
	dollar = 0;
	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++; 
	while (str[*i] && str[*i] != '\"')
	{	
		// printf("in loop\n");
		// printf("BEGIN LOOP:[%d][%c]\n", *i, str[*i]);	
		if (str[*i] == '\\')
		{
			if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '$' || str[(*i) + 1] == '\\' || str[(*i) + 1] == 96)		//Alleen bij "  of $ of \ deleten? Andere tekens? ` ook
				str = delete_escape_char(str, *i);
			if (str[(*i)] == '$')
				(*i)++;
		}
		if (str[*i] == '$')
			str = if_dollar(str, i, _env, 1);			//Dollar binnen quotes
		// printf("NA: {%s} [%d][%c], Next = [%d][%c] = \n", str, *i, str[*i], *i + 1, str[*i + 1]);
		(*i)++;
		// printf("EIND LOOP:[%d][%c]\n", *i, str[*i]);
		// printf("EIND LOOP:[%d][%c]\n", *i, str[*i]);
	}
	// printf("UIT LOOP\n");
	end = *i;							// waarom stond dit erachter? ++;
	// printf(" str DQ: [%s] [%c] [%c]\n", str, str[start], str[end]);									
	str = delete_double_quotes(str, start, end);
	// printf(" str DQ: [%s]\n", str);	
	*i = end - 2; 					// beter niet -1 want beter laten eindigen op laatste char van deze reeks.
	*flag = 1;
	if (dollar == 1)
		str = ft_substr(str, 1, ft_strlen(str));
	return (str);
}

static char			*treat_single_quote(char *str, int *i, int *flag)
{
	int end;
	int  dollar;
	
	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
	str = delete_quotes(str, '\'');				//Freeen oude malloc?
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
		str = ft_substr(str, 1, ft_strlen(str));
	return (str);
}

/*
** Check_builtin_again: check _env variables ($) for commands.
** Ex. export LS="ls -la" 
**
TO DO:
- Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).
*/

void							check_specials(t_command **command, t_env *_env)
{
	int y;
	int i;
	int flag;
	
	y = 0;
	// tester(NULL, *command);
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while((*command)->array && (*command)->array[y] && (*command)->array[y][i])
		{
			flag = 0;
			if (is_single_quote((*command)->array[y][i]) && !flag)
				(*command)->array[y] = treat_single_quote((*command)->array[y], &i, &flag);
			if (is_double_quote((*command)->array[y][i]) && !flag)
			{
				(*command)->array[y] = treat_double_quote((*command)->array[y], &i, _env, &flag);
				// printf("NA DQ:(*command)->array[y] = [%s]\n", (*command)->array[y]);
			}
			if (!is_single_quote((*command)->array[y][i]) && !is_double_quote((*command)->array[y][i]) && !flag)
			{
				if ((*command)->array[y][i] == '\\')
				{
					// printf("(*command)->array[y] = [%s]\n", (*command)->array[y]); 
					(*command)->array[y] = delete_escape_char((*command)->array[y], i);
					i++;
				}
				if ((*command)->array[y][i] == '$' && (*command)->array[y][i + 1] == '\\')		//alleen als buiten haakjes
				{
					(*command)->array[y] = delete_escape_char((*command)->array[y], (i + 1));
					i++;
				}
				if ((*command)->array[y][i] == '$')
				{
					// printf("hier\n");
					(*command)->array[y]  = if_dollar((*command)->array[y] , &i, _env, 0); //new &i
					// printf("(*command)->array[y][%d] = [%c] --> [%s]\n", i, (*command)->array[y][i],  (*command)->array[y]); 
					check_builtin_again(command, _env, y);
				}
			}
			if ((*command)->array[y] == NULL)
			{
				parameter_not_exist(command, &y);
				break;				//MOETEN BREAK HEBBEN v.w. seg
			}
			i++;
			// printf("NEXT i[%d] = [%c] --> [%s]\n", i, (*command)->array[y][i],  (*command)->array[y]); 
		}
		y++;
	}
	// printf("Hier\n");
}

	// printf("UIT CHECK SPECIAL\n");
					// printf("(*command)->array[y] = [%s] en i[%d] = %c\n", (*command)->array[y], i, (*command)->array[y][i]);
			// printf("------------------check specials[%s]\n",(*command)->array[y]);
					// printf("je moet nog een doller plakken\n");
					// i--;			//new of if ((*command)->array[y][i] != '$') boven i++;
			// if ((*command)->array[y][i] != '$')
			
			
				// if ((*command)->array[y][i] == '$' && (*command)->array[y][i+1] == '\\')
				// {
				// 	(*command)->array[y]  = if_dollar((*command)->array[y] , &i, _env);
				// 	(*command)->array[y] = ft_strjoin("$",(*command)->array[y]);
				// }