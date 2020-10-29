/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 12:58:48 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TO DO:
	- Single quotes: //Freeen oude malloc?
	!!! - Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).	
*/

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
** 	- Inner single quotes are considered as text, don't have to be complete.
*/


// char		*make_tmp(char **str)
// {
// 	char *tmp;

// 	// printf("make tmp: *str = [%p][%s], &*str = [%p] --> **str [%p] &[%p]\n", *str, *str, &*str, str, &str);
// 	tmp = ft_strdup(*str);
// 	// printf("make TMP= [%p][%s] [%p]\n", tmp, tmp, &tmp);
// 	// printf("make tmp free(str) = [%p]\n", *str);
// 	free(*str);
// 	*str = NULL;
// 	// printf("make tmp N= [%p][%s]\n", str, str);
// 	return (tmp);
// }


	// printf("------------------Treat double quote---------------\n");
	// str = check_backslash_and_dollar(str, i, _env); //deze?
	///
	// tmp = make_tmp(&str);
	// str = delete_double_quotes(str, start, end);
static char		*treat_double_quote(char *str, int *i, t_env *_env, int *flag)
{
	int		dollar;
	int		start;
	int		end;
	char 	*tmp;
	
	start = *i;
	dollar = 0;
	if (str[*i - 1] == '$')
		dollar = 1;
			
		tmp = ft_strdup(str);
		free(str);
		str = NULL;
		str = check_backslash_and_dollar(tmp, i, _env);
	end = *i;
		tmp = ft_strdup(str);
		free(str);								
		str = NULL;
		str = delete_double_quotes(tmp, start, end);		//tmp wordt al gefreeed
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);								
		str = NULL;
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		free(tmp);
	}
	return (str);
}

		///
		///
		// str = ft_substr(str, 1, ft_strlen(str));
		// tmp = make_tmp(&str);

	// printf("------------------Treat single quote---------------\n");
	// printf("Single quote str= [%p][%s] .   [%p]\n", str, str, &str);
	//MAKE TMP:
	// tmp = make_tmp(&str);		//TEST
	// printf("Single quote tmp = [%p][%s] .  [%p]\n", tmp, tmp, &tmp);
	// printf("Single quote str= [%p][%s] .   [%p]\n", str, str, &str);
	// printf("Single quote str= [%p][%s] .   [%p]\n", str, str, &str);		//lijkt alsof hij weer adres pakt van binnenkomst.
	///
	// str = delete_quotes(str, '\'');		//Die wordt meegegeven wordt bevrijd


static char		*treat_single_quote(char *str, int *i, int *flag)
{
	int		end;
	int		dollar;
	char 	*tmp;
	
	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
		tmp = ft_strdup(str);
		free(str);
		str = NULL;
		str = delete_quotes(tmp, '\'');					//tmp wordt al gefreed
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);
		str = NULL;
		str = ft_substr(tmp, 1, ft_strlen(tmp));		//tmp nog niet gefreed
		free(tmp);
	}
	return (str);
}

		// tmp = make_tmp(&str);

		///
		// str = ft_substr(str, 1, ft_strlen(str));



/*
** Check_builtin_again: checks if there are commands in the _env variables ($)
** Ex. export LS="ls -la" 
*/
		// printf("[%p]\n", (*command)->array[y]);
	// printf("------------------NO quote---------------\n");
		////
		// tmp = make_tmp(&(*command)->array[y]);	///
		// (*command)->array[y] = delete_escape_char((*command)->array[y],
		// 											 (*i + 1));

static void		if_no_quote(t_command **command, t_env *_env, int y, int *i)
{
	char *tmp;
	
	if ((*command)->array[y][*i] == '\\')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = delete_escape_char(tmp, *i);				//tmp wordt gefreeeet
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$' &&
			(*command)->array[y][*i + 1] == '\\')						//Deze kan ik misschien nog samenvoegen met die daarboven 
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = delete_escape_char(tmp, (*i + 1));		//tmp wordt gefreet
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y]  = if_dollar(tmp, i, _env, 0);
		check_builtin_again(command, _env, y);
	}
}

		// (*command)->array[y]  = if_dollar((*command)->array[y] , i, _env, 0);
		// tmp = make_tmp(&(*command)->array[y]);

		// (*command)->array[y] = treat_single_quote((*command)->array[y], i,
		// 											flag);
		// (*command)->array[y] = treat_double_quote((*command)->array[y], i, _env, flag);


		// printf("----V = [%p][%s] -> &[%p]\n", (*command)->array[y], (*command)->array[y], &(*command)->array[y]);
		// tmp = make_tmp(&(*command)->array[y]);
		//MAKE TMP:
		// char *tmp;
		//END TMP
		// printf("----V = [%p][%s] -> &[%p]\n", (*command)->array[y], (*command)->array[y], &(*command)->array[y]);
		// printf("----V tmp = [%p][%s] .  [%p]\n", tmp, tmp, &tmp);
		// printf("After single quote: = [%p][%s]\n", (*command)->array[y], (*command)->array[y]);
		// tmp = make_tmp(&(*command)->array[y]); //TEST
		//MAKE TMP:
		// char *tmp;
		
static void		check_if_quotes(t_command **command, int *flag, int y, int *i,
									t_env *_env)
{
	char *tmp;
	
	if (is_single_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = treat_single_quote(tmp, i, flag);			//tmp wordt gefreeed
		
	}
	if (is_double_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);	
		(*command)->array[y] = NULL;
		(*command)->array[y] = treat_double_quote(tmp, i, _env, flag);
	}
	return ;											
}
	
	// printf("After double quote: = [%p][%s]\n", (*command)->array[y], (*command)->array[y]);
	// printf("------------------Check specials---------------\n");
			// printf("CS1: i = [%d][%c]   [%p]\n", i, (*command)->array[y][i], (*command)->array[y]);
			// printf("CS2: i = [%d][%c]   [%p]\n", i, (*command)->array[y][i], (*command)->array[y]);
			// printf("CS3: i = [%d][%c]   [%p]\n", i, (*command)->array[y][i], (*command)->array[y]);

void			check_specials(t_command **command, t_env *_env)
{
	int		y;
	int		i;
	int		flag;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while ((*command)->array && (*command)->array[y] &&
			(*command)->array[y][i])
		{
			flag = 0;
			check_if_quotes(command, &flag, y, &i, _env);
			if (!is_single_quote((*command)->array[y][i]) &&
				!is_double_quote((*command)->array[y][i]) && !flag)
				if_no_quote(command, _env, y, &i);
			if ((*command)->array[y] == NULL)
			{
				parameter_not_exist(command, &y);
				break;
			}
			i++;
		}	
		y++;
	}
}
