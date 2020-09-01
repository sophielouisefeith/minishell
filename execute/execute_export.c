/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/08/31 19:46:52 by SophieLouis   ########   odam.nl         */
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
** 
** TO DO:
** Child processes nu ook al gecovered? Uitzoeken.
** twee commands kwestie van een whileloopi toevoegen
** error melding als spaties tussen = 
*/


/*
** hij errorrt op unset USER malloc

*/


void        execute_env(t_env *env)
{
    t_env   *list;

    list = env;
    while (list)                                          //misschien beter om eigen printf te gebruiken?
    {
        write(1, list->name, ft_strlen(list->name));
        write(1, "=", 1);
        write(1, list->value, ft_strlen(list->value));
        write(1, "\n", 1);
        list = list->next;
    }
}

static int          check_format(char *str)
{
    int i;
    printf("in format\n");
    if (!ft_isalpha(*str))
    {
        strerror(2);
        printf("not a valid identifier\n");
        return (1);
    }
    i = 1;
    while ((ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_') && str)
        i++;
    if (str[i] == '=')
        return (0);                
    else if (str[i] == '\0')
       return (1);                 
    // else
    // {
    //     strerror(error_notavalidentifier);
    //     printf("not a valid identifier\n");
    //     return (2);                 
    // }
    return(0);
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
	write(1, "\n", 1);
}

static int             print_declare_x_env(t_env **_env)
{
    t_env   *list;
	t_env   *alpha_env;
	alpha_env = *_env;
	alpha_env_list(alpha_env);
   	list = alpha_env;
	printf("kom je hier\n");
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
    return (0);
}



static int        not_present_in_env(char **array, t_env **_env, int equal)
{

	t_env   *tmp;
	tmp = ll_new_node_env(array[0], array[1], equal);
    ll_lstadd_back_env(_env, tmp);
	return(0);
}



static int        check_present_in_env(char **array, t_env **_env, int equal)
{
    t_env   *list;
    char    *str;
	
    list = *_env;
    while (list)
    {		
        if (!ft_strcmp(array[0], list->name)) //dit betekend dat de naam gelijk is
		{
			if (!ft_strcmp(array[0], list->name)) 	
			{
				if(equal)
				{
					list->equal = 1;
					list->value = "";
                    if(ft_strcmp(array[1], list->value))			//vervang als ongelijke waarde
						list->value = array[1];
				}
				return(0);
			}
            if(array[1])
            {
                str = array[1];
                if(str[0] == '$')
                    list->value = (*_env)->value;
            }
                
			if (!ft_strcmp(array[1], list->value)) // dit betekend dat de value gelijk is
				return(0);
			else
			{
				list->value = array[1];  // dit betekend dat de value aangepast moet worden
				return(0);
			}
		}
		list = list->next;
	}
	not_present_in_env(array, _env, equal);
	return(0); 				
}

int            execute_export(t_env **_env, t_command **command)
{
   	char    **array;
	int		i;
	int		equal;
	int		check;
    int     ret;

	equal = 0;
    check = 0;
    if((*command)->array == '\0')
    {
		printf("GEEN ARGUMENTEN\n");
        print_declare_x_env(_env);
        return (0);
    }
    if(ft_strrchr((*command)->array[0], 61))
        equal = 1;
	i = 0;
	while ((*command)->array[i] && (*command)->array[i] !='\0')
	{
		array = ft_split((*command)->array[i], '=');
		check_format(*array);
		printf("array---name[%s]\n", array[0]);
		printf("array---value[%s]\n", array[1]);
		i++;
	}
   	check = check_present_in_env(array, _env, equal);
    return(0);
}












	// 	if(!list->next && i == 4)
    //     {   
    //        	printf("je komt in 4\n");
    //         write(1, "declare-x ", 10);
    //         write(1, list->name, ft_strlen(list->name));
    //        	write(1, "\"",1);
    //         write(1, "\"", 1);
    //         write(1, "\n", 1);
	// 		printf("Seg4\n");
    //         return(0);
    //     }
    //     if(!list->next && i == 2)
    //     {   
    //        printf("je komt in 2\n");
    //         write(1, "declare-x ", 10);
    //         write(1, list->name, ft_strlen(list->name));
    //     //    write(1, "\"", 1);
	// 	//    write(1, "\"", 1);
    //         write(1, "\n", 1);
    //         return(0);
    //     }
    //     if(!list->next && i == 3)
    //     {   
    //         //printf("je komt in 3\n");
    //         write(1, "declare-x ", 10);
    //         write(1, list->name, ft_strlen(list->name));
    //        write(1, "=", 1);
    //        write(1, "\"",1);
	// 	   write(1, list->value, ft_strlen(list->value));
    //         write(1, "\"", 1);
	// 		write(1, "\n", 1);
    //         return(0);
    //     }
	// 	write(1, "\n", 1);