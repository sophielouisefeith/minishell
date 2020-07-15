
#include <stdlib.h>
#include <stdio.h>

typedef struct      s_list
{
    char               *data;
    struct s_list      *next;
           
}                   t_list;

int				main(int argc, char **argv)
{
    
    t_list *first;
    t_list *second; 
    t_list *third;

    first = (t_list*)malloc(sizeof(t_list));
    second = (t_list*)malloc(sizeof(t_list));
    third = (t_list*)malloc(sizeof(t_list));

    first->data = 1;
    first->next = second;
    second->data = 2;
    second->next = third;
    third->data = 3;
    printf("%d\n", first->next->data);
    //third->next;
}