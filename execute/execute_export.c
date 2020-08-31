/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/08/31 13:04:09 by msiemons      ########   odam.nl         */
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
*/


/*
** hij errorrt op unset USER malloc


*/



/*
** 0 = Bestaat 
** 1 = 
**/

static int          check_present_in_env(char **array, t_env **_env)
{
    t_env   *list;

    list = *_env;
	// printf("-------------------name[%s]\n", list->name);
    while (list)
    {		
        if (!ft_strcmp(array[0], list->name)) //dit betekend dat de naam gelijk is
		{
            printf("--------------------------de naam is gelijk\n");
			if (!ft_strcmp(array[1], list->value)) // dit betekend dat de value gelijk is
			{
				printf("-----------------------je  bent helemaal gelijk\n");
				return(0);
			}
			else
			{
				list->value = array[1];  // dit betekend dat de value aangepast moet worden 
				// printf("-------------------nieuwe value[%s]\n", list->value);
				return(1);
			}
		}
		list = list->next;
    }
    return (2);									//geen gelijke vind opnnieeuw aanmaken
}



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
        //return (1);
    }
    i = 1;
    while ((ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_') && str)
        i++;
    if (str[i] == '=')
        return (0);                
    // else if (str[i] == '\0')
    //    // return (1);                 
    else
    {
        strerror(error_notavalidentifier);
        printf("not a valid identifier\n");
        //return (2);                 
    }
    return(0);
}

static void	swap(char **s1, char **s2)
{
	char *tmp;

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
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
	write(1, "\n", 1);
}

static int             print_declare_x_env(t_env **_env, int  i)
{
    t_env   *list;
	t_env   *alpha_env;
	
	alpha_env = *_env;
	alpha_env_list(alpha_env);
   	list = alpha_env;
  	printf("je gaat nu schrijven\n");
    while(list)                                         
    {
        write(1, "declare-x ", 10);
        write(1, list->name, ft_strlen(list->name));
        
		write(1, "=", 1);
        
		write(1, "\"", 1);
        
		write(1, list->value, ft_strlen(list->value));
        
		write(1, "\"", 1);
       	
		write(1, "\n", 1);
		
        // if(!list->next  && i ==3)
        // {
        //     printf(" haakjes\n");
        //     write(1, "\"\"", 4);
        //     //return(0);
        // }
        
        list = list->next;
		// if(!list->next && i == 4)
        // {   
        //     printf("je komt in 4\n");
        //     write(1, "declare-x ", 10);
        //     write(1, list->name, ft_strlen(list->name));
        //    // write(1, "=", 1);
        //    	write(1, "\"",1);
        //     write(1, "\"", 1);
        //     write(1, "\n", 1);
        //     return(0);
        // }
        if(!list->next && i == 2)
        {   
            printf("je komt in 2\n");
            write(1, "declare-x ", 10);
            write(1, list->name, ft_strlen(list->name));
           // write(1, "=", 1);
           // write(1, "''",2);
            write(1, "\n", 1);
            return(0);
        }
        // if(!list->next && i == 3)
        // {   
        //     printf("je komt in 3\n");
        //     write(1, "declare-x ", 10);
        //     write(1, list->name, ft_strlen(list->name));
        //    write(1, "=", 1);
        //    write(1, "\"",1);
		//    write(1, list->value, ft_strlen(list->value));
        //     write(1, "\"", 1);
		// 	write(1, "\n", 1);
        //     return(0);
        // }
        //list = list->next;
       //	write(1, "\n", 1);
    }
    return (0);
}

int            execute_export(t_env **_env, t_command **command)
{
	t_env   *tmp;
   t_env   *copy_env;
   	char    **array;
    int     ret;
	int		i;
	int		exsist;
    int     equel;
    char    *c_equel;

    c_equel = "=";
    equel = 0;
    copy_env = *_env;
    exsist = 0;
    if((*command)->array == '\0')
    {
        print_declare_x_env(&copy_env, 0);  //trial met copy
        return(0);
    }
    if(ft_strrchr((*command)->array[0], 61))
        equel++;   
	i = 0;
	while ((*command)->array[i] && (*command)->array[i] !='\0')
	{
		array = ft_split((*command)->array[i], '=');
		//ret = check_format(*array);
		printf("array---name[%s]\n", array[0]);
		printf("array---value[%s]\n", array[1]);
		i++;
	}
    exsist = check_present_in_env(array, _env);
	if(!exsist)
        print_declare_x_env(_env, 0);
    if(exsist)
    {
        if(exsist == 1 && equel)
		{
			printf("exsist == 1\n");
            print_declare_x_env(_env, 1); //newvalue
		}
        if(exsist == 2) // hier moet hij dus in de env toegevoegd worden en in export wel in alphabethvolgorde
        {
            printf("---------------je word nieuw toegevoegd\n");
            if(equel)
            {
                printf("equel\n");
                if(array[1])  // er zit dus iets achter de equel dan moet dat ook toegevoegd worden
                {
                    //printf("new-----value & name");
                     printf("---------------------------------------------array[1] word ook toegevoegd met haakjes\n");
                   // *array[1] = ft_strlcat(array[1], "\"", 100); // dubbele haakjes om de array
                    printf("----------------------------------------------value[%s]\n", array[1]);
                    //ft_strlcat(array[0], c_equel, ft_strlen(array[0] +2)); // dubbele haakjes om de array
                    tmp = ll_new_node_env(array[0], array[1], 1);
                    ll_lstadd_back_env(_env, tmp);
                    print_declare_x_env(_env, 3);
                }
                else // er zit niks achter de equel
                {
                    printf("--------------------------------------------toegevoegd niks achter\n");
                    tmp = ll_new_node_env(array[0], array[1], 1);
                    ll_lstadd_back_env(_env, tmp);
                    print_declare_x_env(_env, 4);
                    return(0);
                }
            }
            else 
            {
                printf("toegevoegd\n");
                tmp = ll_new_node_env(array[0], array[1], 0); // hier gaat hij nog fout
                ll_lstadd_back_env(_env, tmp);
                print_declare_x_env(_env, 2);
                return(0); 
           }
		   
        }
    }
	printf("komt hier nog\n");
    return (0);
}
