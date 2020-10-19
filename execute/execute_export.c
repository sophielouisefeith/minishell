/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/10/14 11:55:11 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "string.h"

/*
** Export command is used to export a variable to the environment 
** of all the child processes running in the current shell.
**
** 1. Check of voldoet aan formar name=value
        - eerste char moet char zijn
        - er kunnen geen speciale chars in name zitten BEHALVE un0derscore
       - geen = dan gebeurt er niets
        - wel = dan var aangemaakt  
** 2. Check of al in env zit
**   zo ja --> verander value
**   zo nee --> maak nieuw aan

** TO DO:
** - Child processes nu ook al gecovered? Uitzoeken.
** - twee commands kwestie van een whileloopi toevoegen [Check]
** - error melding als spaties tussen = 
** - return values
*/

/*
** hij errorrt op unset USER malloc
*/



// static int			is_special_char(char *str, int i)
// {
// 	printf("special\n");
// 	// while (str[i])
// 	// {
// 		if(str[i] == '$' && str[i] + 1 == '\0')
// 			return(1);
// 		if (ft_isprint(str[i]) && !c && str[i] != '_')
// 			return (1);
// 	// 	i++;
// 	// }
// 	return (0);
// }

static int          check_format(char *str)
{
    int i;
	
    if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
    i = 1;
	//printf("kom je hier nog\n");
    while ((ft_isalnum(str[i])|| str[i] == '_') && str)
        i++;
	if ((!ft_isalnum(str[i])|| str[i] != '_') && str[i] != '\0')  // hier moet dan nog een $bij ?
		return (-1);
    // if (str[i] == '=')		//Zit geen = in str
    //     return (0);
	// if (str[i]== '\0')                           
    // 	return(0);
	return (0);
}

static void	swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;	
}

static void	swap_int(int *s1, int *s2)
{
	int tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;	
}

static void alpha_env_list(t_env *alpha_env)
{
	t_env		*list1;
	t_env		*list2;
	int			compare;
	
	list1 = alpha_env;
	while(list1 && list1->next)
	{
		list2 = list1->next;
		while(list2)
		{

			compare = ft_strcmp(list1->name, list2->name);
			if(compare > 0)
			{
				swap(&list1->name, &list2->name);
				swap(&list1->value, &list2->value);
				swap_int(&list1->equal, &list2->equal);
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}

/*
** To do;
	- write errors? mwah
*/

static void             print_declare_x_env(t_env **_env)
{
    t_env   *list;
	t_env   *alpha_env;

	alpha_env = *_env;
	alpha_env_list(alpha_env);
   	list = alpha_env;
    while (list)                                         
    {
        write(1, "declare-x ", 10);
        write(1, list->name, ft_strlen(list->name));
		if (list->equal)
		{
        	write(1, "=", 1);
        	write(1, "\"", 1);
       		if(list->value)
				write(1, list->value, ft_strlen(list->value));
			write(1, "\"", 1);   
		}
       	write(1, "\n", 1);
        list = list->next;
    }
}

static int        not_present_in_env(char **array, t_env **_env, int equal)
{
	t_env   *tmp;
	tmp = ll_new_node_env(array[0], array[1], equal);
    ll_lstadd_back_env(_env, tmp);
	return (0);
}

static int        check_present_in_env(char **array, t_env **_env, int equal)
{
    t_env   *list;
	
    list = *_env;
    while (list)
    {		
        if (!ft_strcmp(array[0], list->name)) 			//dit betekend dat de naam gelijk is
		{
			if (equal)
			{
					list->equal = 1;
					if (!array[1])
						list->value = "";
					else if (ft_strcmp(array[1], list->value))
						list->value = array[1];
			}
			return (0);
		}
		list = list->next;
	}
	not_present_in_env(array, _env, equal);
	return (0); 				
}

int            execute_export(t_env **_env, t_command **command)
{
   	char    **array;
	int		equal;
	int 	ret;
	int		i;

	equal = 0;
	i = 0;
	if (!(*command)->array)
    {
        print_declare_x_env(_env);
        return (0);
    }
    if (ft_strrchr((*command)->array[0], '='))
        equal = 1;
	while ((*command)->array[i] && (*command)->array[i] !='\0')
	{
		
		array = ft_split2((*command)->array[i], '=');
		ret = check_format(array[0]);
		if (ret == -1)
		{
			// if((*command)->array[i], '_'
			//printf("command-[%s]", (*command)->array[i]);
			//printf(" export: `arg1': not a valid identifier\n");
			//error((*command)->array[i]);  
			return(error(*command));				//new
			//return (-1);                         //new
		}
   		check_present_in_env(array, _env, equal);
		free(array);
		i++;
	}
    return (0);
}
