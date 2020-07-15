/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 13:54:08 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/15 14:04:20 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

static int		ft_wordcount(char const *s, char c)
{
	int		i;
	int		wcount;

	i = 0;
	wcount = 0;
	if (c == '\0' && s[i] != '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			wcount++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (wcount);
}

static int		ft_lettercount(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char		**ft_freenewstring(char **ns, int j)
{
	while (j >= 0)
	{
		j--;
		if (ns[j])
			free(ns[j]);
	}
	if (ns)
		free(ns);
	return (NULL);
}

t_list	*ft_lstnew(char  *content)
{
	t_list *node;
  

	node = malloc(sizeof(t_list));
	if (node)
	{
		node->data = content;
		node->next = NULL;
	}
	return (node);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *temp; // maak een kopie van de head 

	temp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;			//want hier verplaatse we de kopie van de head
	}
}

t_list			*split(char const *s, char c)
{
	int		wc;
	int i;
	int lcount;
	int j;
	char *str;
    t_list *tmp;
	t_list *head;
  
	j = 0;
	i = 0;
	tmp = NULL;
	head = NULL;
	if (!s)
		return (NULL);
	i = 0;
	wc = ft_wordcount(s, c);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			lcount = ft_lettercount(s, c, i);
            str = ft_substr((char *)s, i, (size_t)lcount);
			tmp = ft_lstnew(str);
			ft_lstadd_back(&head, tmp);
			while (s[i] != c && s[i] != '\0')
			i++;
		}
	}
    printf("list1[%s]\n", head->data);
	printf("list2[%s]\n", head->next->data);
	return (head);
	
}